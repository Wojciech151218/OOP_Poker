//
// Created by wojciech on 11/6/24.
//

#include "../headers/GameState.h"

#include <random>


#include "iostream"
#include "../headers/Hand.h"
#include "../headers/utils.h"


void GameState::deal_cards()
{
    for(Player & player : players)
    {
        std::vector cards = {deck.draw(),deck.draw()};
        player.set_cards(cards);
    }
}

void GameState::increment_phase(GamePhase& phase)
{
    if (phase == River) {
        phase = PreFlop;
    } else {
        phase = static_cast<GamePhase>(phase + 1);
    }
}

void GameState::reset_phase()
{
    betting_player = std::nullopt;
    current_bet = 0;
    current_player = 0;
    while(players[current_player].get_status() != Player::InGame) {
        current_player++;
    }
    player_bets = std::vector<size_t>(players.size(),0);
}

std::string GameState::phase_to_string()
{
    switch (phase)
    {
    case PreFlop:
        return "pre-flop";
    case Flop:
        return "flop";
    case Turn:
        return "turn";
    case River:
        return "river";
    }
}

GameState::GameState(const std::vector<Player>& players, const GameProperties& game_properties)
    :players(players),game_properties(game_properties)
{
    transition_state = NotTransition;
    current_bet =0;
    folded_players =0;
    pot =0;
    table = {};
    deck = Deck();
    phase = PreFlop;
    current_player = 0;
    betting_player = std::nullopt;
    player_bets = std::vector<size_t>(players.size(),0);
    round_result = std::nullopt;

    deal_cards();

}

void GameState::print_state()
{

    players[current_player].print_player_status();
    std::cout<< phase_to_string()<<"\n";
    print_table_card();
    std::cout<<"player "<<current_player<<"\n";
    std::cout<<"pot "<<pot<<"\n";
    std::cout<<"to call "<< current_bet <<"\n";



}
void GameState::process_action(const Action& action) {

    if(transition_state == AllIn) {
        handle_phase_transition();
        return;
    }
    auto bet = players[current_player].do_action(action, current_bet);

    handle_action(action, bet);

    if (is_game_folded()) {
        return;
    }

    bool is_phase_trasnstion  =  increment_player();
    if(is_game_allined() && is_phase_trasnstion) {
        transition_state = AllIn;
        return;
    }

    if (is_phase_trasnstion) {
        handle_phase_transition();
    }


}

void GameState::handle_action(const Action &action, int bet) {
    player_bets[current_player] = bet;
    switch (action.get_action_type()) {
    case Action::Fold:

        folded_players++;
        break;
    case Action::BetRaise:
        betting_player =  current_bet < bet ?  current_player : betting_player;
        current_bet = bet;

        pot+= bet;
        break;
    case  Action::CheckCall:
        pot+= bet;
        break;
    }
}

bool GameState::is_game_folded() const {
    return folded_players >= players.size() - 1;
}
bool GameState::is_game_allined()const {
    int allined_players = 0;
    for(let & player : players) {
        if(player.get_status() == Player::AllIn)
            allined_players++;
    }
    let playing_players = players.size() - folded_players;
    return playing_players == allined_players;
}

void GameState::handle_round_end() {
  distribute_pot();
  reset_game_state();
}

bool GameState::increment_player() {
    auto no_bet_turn_result = false;
    current_player++;
    if(current_player == players.size())
        current_player = 0;
    if(current_player == betting_player )
        return true;

    no_bet_turn_result = (betting_player == std::nullopt && current_player ==0) || no_bet_turn_result;

    while(players[current_player].get_status() != Player::InGame ) {
        no_bet_turn_result = (betting_player == std::nullopt && current_player ==0) || no_bet_turn_result;

        current_player++;
        if(current_player == players.size())
            current_player = 0;
    }
    if(current_player == betting_player )
        return true;



    return no_bet_turn_result;
}

void GameState::handle_phase_transition() {
    switch (phase) {
    case River:
        handle_round_end();
        return;

    case PreFlop:
        deal_flop();
        break;

    default:
        deal_next_card();
        break;
    }
    reset_phase();
    increment_phase(phase);

}

void GameState::deal_flop() {
    for (int i = 0; i < 3; i++) {
        table.push_back(deck.draw());
    }
}

void GameState::deal_next_card() {
    table.push_back(deck.draw());
}


Action::ActionType GameState::make_random_action() {
    // Initialize random number generator
    std::random_device random_device; // Non-deterministic seed
    std::mt19937 random_engine(random_device()); // Mersenne Twister engine
    std::uniform_real_distribution<double> uniform_distribution(0.0, 1.0); // Uniform distribution in range [0.0, 1.0)

    // Generate a random double
    double random_probability = uniform_distribution(random_engine);

    // Define action probability ranges
    std::vector<std::pair<double, Action::ActionType>> action_probabilities = {
        {0.25, Action::Fold},
        {0.25, Action::BetRaise},
        {0.5, Action::CheckCall}
    };

    // Ensure the probabilities sum to 1.0
    double total_probability = 0.0;
    for (let& action : action_probabilities) {
        total_probability += action.first;
    }

    if (std::abs(total_probability - 1.0) > 1e-9) { // Error if total probability isn't close to 1.0
        throw std::runtime_error("Action probabilities must sum to 1.0.");
    }

    // Determine the action based on random probability
    double cumulative_probability = 0.0;
    Action::ActionType selected_action_type = Action::Fold; // Default action

    for (let& action : action_probabilities) {
        cumulative_probability += action.first;
        if (random_probability < cumulative_probability) {
            selected_action_type = action.second;
            break;
        }
    }

    // Determine bet size based on selected action
    int bet_size = (selected_action_type == Action::BetRaise) ? current_bet + 25 : 0;

    // Process the selected action
    process_action(Action(bet_size, selected_action_type));
    return selected_action_type;
}



bool GameState::check_if_is_current_player(size_t player) const {
  return player == current_player;
}

const Player &GameState::get_current_player() const {
  return players[current_player];
}
std::string GameState::get_phase_as_string() const {
  switch (phase) {
  case PreFlop:
    return "PreFlop";
  case Flop:
    return "Flop";
  case Turn:
    return "Turn";
  case River:
    return "River";
  }
}


void GameState::reset_game_state()
{
    transition_state = NotTransition;
    table.clear();
    deck = Deck();
    phase = PreFlop;
    folded_players = 0;
    betting_player = std::nullopt;
    deal_cards();
    pot = 0;
    current_player = 0;
    for(auto & player : players) {
        player.reset_status();
    }
    reset_phase();


}

void GameState::distribute_pot()
{
    let hand = Hand(table);
    let winners = hand.get_outcome(players);
    let split = winners.size();
    auto winners_copy_vector = std::vector<Player>();
    for(let winner :winners){
        winner.get().give_earnings(pot/split);
        winners_copy_vector.emplace_back(winner.get());
    }
    round_result = GameResult(table,winners_copy_vector);
}

void GameState::print_table_card() const {
  for (let &card : table) {
    std::cout << card.to_string() << " ";
  }
  std::cout << '\n';
}
std::optional<GameResult> GameState::get_round_result() const {
  return round_result;
}
void GameState::reset_round_result() {
    round_result = std::nullopt;
}