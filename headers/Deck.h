//
// Created by wojciech on 11/6/24.
//

#ifndef DECK_H
#define DECK_H
#include <vector>

#include "Card.h"


class Deck {
    std::vector<Card> deck;

public:
    Deck();
    Card draw();
};



#endif //DECK_H
