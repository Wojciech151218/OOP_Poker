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
    calling_players =0;
    current_bet = 0;
    current_player = 0;
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
    current_bet =0;
    pot =0;
    table = {};
    deck = Deck();
    phase = PreFlop;
    current_player = 0;
    calling_players =0;
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

void GameState::process_action(const Action& action)
{

    auto bet = players[current_player].do_action(action, calling_players, current_bet);
    let player_status = players[current_player].get_status();

    switch(player_status) {
    case Player::Fold:
        folded_players.emplace_back(current_player);
        break;

    default:
        pot += bet;
        if(bet > current_bet)
            current_bet = bet;

        break;
    }
    if(folded_players.size() >= players.size()-1)
    {
        distribute_pot();
        reset_game_state();
        return;
    }


    current_player++;

    if(current_player == players.size())
    {
        if(players.size() - folded_players.size() > calling_players)
        {
            current_player = 0;
            return;
        }
        switch (phase)
        {
        case River:
            reset_game_state();
            distribute_pot();
            break;
        case PreFlop:
            for (auto i =0; i<3 ;i++)
                table.push_back(deck.draw());
            break;
        default:
            table.push_back(deck.draw());
            break;

        }
        reset_phase();
        increment_phase(phase);

    }
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
        {0.1, Action::Fold},
        {0.1, Action::BetRaise},
        {0.8, Action::CheckCall}
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
    int bet_size = (selected_action_type == Action::BetRaise) ? 20 : 0;

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
void GameState::reset_game_state()
{

    table.clear();
    deck = Deck();
    phase = PreFlop;
    player_bets.clear();
    deal_cards();
    pot = 0;
    current_player = 0;
    reset_phase();


}

void GameState::distribute_pot()
{
    let hand = Hand(table);
    let winners = hand.get_outcome(players);
    let split = winners.size();
    for(let winner :winners){
        winner.get().give_earnings(pot/split);
    }
}

void GameState::print_table_card() const
{
    for (let & card : table )
    {
        std::cout<< card.to_string()<<" ";
    }
    std::cout<<'\n';


}
