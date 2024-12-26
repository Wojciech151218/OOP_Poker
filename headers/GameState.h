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
    void process_action(const Action &action);
    Action::ActionType make_random_action();
    bool check_if_is_current_player(size_t player)const;

    size_t get_calling_players() const { return calling_players; }
    std::vector<size_t> get_folded_players() const { return folded_players; }
    GameProperties get_game_properties() const { return game_properties; }
    Deck get_deck() const { return deck; }
    std::vector<Card> get_table() const { return table; }
    size_t get_current_player_index() const { return current_player; }
    GamePhase get_phase() const { return phase; }
    size_t get_pot() const { return pot; }
    size_t get_current_bet() const { return current_bet; }
    std::vector<Player> get_players() const { return players; }
    std::vector<size_t> get_player_bets() const { return player_bets; }
    const Player & get_current_player() const;


  private:
    void reset_game_state();
    void distribute_pot();
    void print_table_card()const;
    void deal_cards();
    void increment_phase(GamePhase & phase);
    void reset_phase();
    size_t calling_players;

    std::string phase_to_string();
    std::vector<size_t> folded_players;
    std::vector<size_t> player_bets;

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
