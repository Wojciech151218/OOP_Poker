//
// Created by wojciech on 11/6/24.
//

#ifndef HAND_H
#define HAND_H
#include <vector>

#include "Card.h"
#include "Player.h"


class Hand {
public:
    enum Category{HighCard,Pair,TwoPairs,Set,Straight,Flush,FullHouse,Quads,StraightFlush};
    std::vector<Card> & table;
    Hand(std::vector<Card> & table);
    Category decide(const Player & player) const;
    std::vector<std::reference_wrapper< Player>> get_outcome(std::vector<Player>& players) const;
private:
    size_t get_numerical_category(Hand::Category category) const;


};



#endif //HAND_H
