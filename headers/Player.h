//
// Created by wojciech on 11/6/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <vector>

#include "Action.h"
#include "cstddef"
#include "Card.h"


class Player {

public:
    enum PlayerStatus{InGame,Fold,AllIn};
    void print_player_status();
    size_t do_action(const Action & action, size_t& calling_players, size_t current_bet);
    void set_cards(std::vector<Card> & cards);
    Player(size_t starting_stake);
    PlayerStatus get_status() const;
    size_t get_bank_roll() const;
    size_t get_starting_bet(size_t bet);
    void give_earnings(size_t earnings);
    std::vector<Card> get_pocket_cards() const ;
    static std::string status_to_string(const PlayerStatus & status);


private:
    size_t bank_roll;
    PlayerStatus player_status;
    std::vector<Card> pocket;

};



#endif //PLAYER_H
