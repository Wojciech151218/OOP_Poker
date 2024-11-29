//
// Created by wojciech on 11/6/24.
//

#include "../headers/GameState.h"
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
    folded_players =0;
    current_bet =0;
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
    folded_players =0;
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

    auto bet = players[current_player].do_action(action, calling_players, folded_players, TODO);
    let player_status = players[current_player].get_status();

    switch(player_status) {
    case Player::Fold:
        folded_players++;
        break;

    default:
        pot += bet;
        if(bet > current_bet)
            current_bet = bet;

        break;
    }
    if(folded_players >= players.size()-1)
    {
        distribute_pot();
        reset_game_state();
        return;
    }


    current_player++;

    if(current_player == players.size())
    {
        if(players.size()- folded_players > calling_players)
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

void GameState::reset_game_state()
{

    table.clear();
    deck = Deck();
    phase = PreFlop;
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
    for(let winner :winners)
    {
        winner.get().give_earnings(pot/split);
    }
}

void GameState::print_table_card() const
{
    for (let & card : table )
    {
        card.print();
        std::cout<<" ";
    }
    std::cout<<'\n';


}
