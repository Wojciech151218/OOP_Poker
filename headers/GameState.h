//
// Created by wojciech on 11/6/24.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>

#include "Action.h"
#include "Deck.h"
#include "Player.h"

struct GameProperties
{
    size_t small_bet;
    size_t big_bet;
    size_t increment;
};
class GameState {

public:
    GameState(const std::vector<Player> & players,const GameProperties & game_properties);
    enum GamePhase{PreFlop,Flop,Turn,River};

    void print_state();
    void process_action(const Action& action);



private:
    void reset_game_state();
    void distribute_pot();
    void print_table_card()const;
    void deal_cards();
    void increment_phase(GamePhase & phase);
    void reset_phase();
    size_t calling_players;
    size_t folded_players;
    std::string phase_to_string();
    GameProperties game_properties;
    Deck deck;
    std::vector<Card> table;
    size_t current_player;
    GamePhase phase;
    size_t pot;
    size_t current_bet;
    std::vector<Player> players;


};



#endif //GAMESTATE_H
