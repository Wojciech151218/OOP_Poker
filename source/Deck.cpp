//
// Created by wojciech on 11/6/24.
//

#include "../headers/Deck.h"

#include <random>

#include "../headers/utils.h"


Deck::Deck() {
    // Populate the deck with all combinations of suits and ranks
    for (auto suit : Card::all_suits()) {
        for (auto rank : Card::all_ranks()) {
            deck.emplace_back(suit, rank);
        }
    }

    // Initialize a random number generator with a random seed
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle the deck
    std::shuffle(deck.begin(), deck.end(), gen);
}

Card Deck::draw()
{
    let card = deck.back();
    deck.pop_back();
    return card;
}
