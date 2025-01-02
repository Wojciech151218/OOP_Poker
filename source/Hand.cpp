//
// Created by wojciech on 11/6/24.
//

#include "../headers/Hand.h"
#include "../headers/utils.h"
#include "functional"

Hand::Hand(std::vector<Card>& table):table(table)
{
}

Hand::Category Hand::decide(const Player& player) const
{
    //todo
    return HighCard;
}

std::vector<std::reference_wrapper< Player>> Hand::get_outcome( std::vector<Player>& players) const
{
    std::vector<std::reference_wrapper< Player>> not_folded_players;
    for(auto & player : players) {
        let player_status = player.get_status();
        if(player_status != Player::Fold)
            not_folded_players.emplace_back(player);
    }

    std::vector<std::reference_wrapper< Player>>  strongest_players ;
    auto strongest_hand = decide(players.front());
    for (auto  player : not_folded_players)
    {
        let player_hand = decide(player);
        if(get_numerical_category(strongest_hand) > get_numerical_category(player_hand))
        {
            strongest_players.clear();
            strongest_players.emplace_back(player);
            strongest_hand = player_hand;
        }
        if(get_numerical_category(strongest_hand) == get_numerical_category(player_hand))
            strongest_players.emplace_back(player);
    }
    return strongest_players;



}

size_t Hand::get_numerical_category(Hand::Category category) const{
    switch (category) {
    case Hand::Category::HighCard: return 1;
    case Hand::Category::Pair: return 2;
    case Hand::Category::TwoPairs: return 3;
    case Hand::Category::Set: return 4;
    case Hand::Category::Straight: return 5;
    case Hand::Category::Flush: return 6;
    case Hand::Category::FullHouse: return 7;
    case Hand::Category::Quads: return 8;
    case Hand::Category::StraightFlush: return 9;
    default: return 0; // Optionally handle unexpected values
    }
}
