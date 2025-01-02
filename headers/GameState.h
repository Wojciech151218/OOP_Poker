//
// Created by wojciech on 11/6/24.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <string>

#include "Action.h"
#include "Deck.h"
#include "GameResult.h"
#include "Player.h"

#include <optional>
enum Transition {
    NotTransition,MidPhase,RoundEnd,AllIn
};

struct GameProperties{
    size_t small_bet;
    size_t big_bet;
    size_t increment;
    size_t player_number;
};
class GameState {

public:
    GameState(const std::vector<Player> & players,const GameProperties & game_properties);
    enum GamePhase{PreFlop,Flop,Turn,River};

    void print_state();
    void process_action(const Action &action);
    Action::ActionType make_random_action();
private:
    void handle_action(const Action &action, int bet);
    bool is_game_folded() const;
    bool is_game_allined() const;

    void handle_round_end();
    bool increment_player();
    void handle_phase_transition();
    void deal_flop();
    void deal_next_card();
public:
    bool check_if_is_current_player(size_t player)const;
    bool is_transition() const { return transition_state != NotTransition;}

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
    std::string get_phase_as_string() const;
    std::optional<GameResult> get_round_result() const;
    void reset_round_result();



  private:
    void reset_game_state();
    void distribute_pot();
    void print_table_card()const;
    void deal_cards();
    void increment_phase(GamePhase & phase);
    void reset_phase();

    std::string phase_to_string();
    size_t folded_players;
    std::vector<size_t> player_bets;

    Transition transition_state;
    std::optional<size_t> betting_player;
    GameProperties game_properties;
    Deck deck;
    std::vector<Card> table;
    size_t current_player;
    GamePhase phase;
    size_t pot;
    size_t current_bet;
    std::vector<Player> players;
    std::optional<GameResult> round_result;

};



#endif //GAMESTATE_H
