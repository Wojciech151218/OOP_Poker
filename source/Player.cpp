//
// Created by wojciech on 11/6/24.
//

#include "../headers/Player.h"

#include <iostream>

#include "../headers/utils.h"

void Player::print_player_status()
{
    std::cout<< "bank roll "<< bank_roll<< "\n";
    for (let card : pocket)
        card.print();
    std::cout<<"\n";


}

size_t Player::do_action(const Action& action, size_t& calling_players, size_t current_bet)
{
    if(player_status == Fold) return 0;
    size_t chips_given = 0;
    int bank_roll_int = static_cast<int>(bank_roll);

    switch (action.get_action_type())
    {
    case Action::Fold:
        player_status = Fold;
        return 0;
    case Action::CheckCall:
        bank_roll_int -= static_cast<int>(current_bet);
        chips_given= action.get_bet_size();
        calling_players++;
        if(bank_roll_int<0)
        {
            chips_given += bank_roll_int;
            bank_roll = 0;
        }else
        {
            bank_roll = bank_roll_int;
        }
        break;
    case Action::BetRaise:
        bank_roll_int -= static_cast<int>(action.get_bet_size());
        chips_given= action.get_bet_size();
        calling_players = 0;
        if(bank_roll_int<0)
        {
            chips_given += bank_roll_int;
            bank_roll = 0;
        }else
        {
            bank_roll = bank_roll_int;
        }
        player_status = bank_roll ==0 ? AllIn : InGame;
    }
    return chips_given;

}

void Player::set_cards(std::vector<Card>& cards)
{
    pocket = cards;
}

Player::Player(size_t starting_stake):bank_roll(starting_stake),player_status(InGame)
{

}

Player::PlayerStatus Player::get_status() const
{
    return player_status;
}

void Player::give_earnings(size_t earnings)
{
    bank_roll+= earnings;
}

