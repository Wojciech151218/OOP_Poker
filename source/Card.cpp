//
// Created by wojciech on 11/6/24.
//

#include "../headers/Card.h"

#include <iostream>
#include <string>

std::string Card::to_string() const {
    std::string rank_str;
    std::string suit_str;


    // Convert rank to string
    switch (rank) {
    case Two:   rank_str = "2"; break;
    case Three: rank_str = "3"; break;
    case Four:  rank_str = "4"; break;
    case Five:  rank_str = "5"; break;
    case Six:   rank_str = "6"; break;
    case Seven: rank_str = "7"; break;
    case Eight: rank_str = "8"; break;
    case Nine:  rank_str = "9"; break;
    case Ten:   rank_str = "10"; break;
    case Jack:  rank_str = "J"; break;
    case Queen: rank_str = "Q"; break;
    case King:  rank_str = "K"; break;
    case Ace:   rank_str = "A"; break;
    }

    // Convert suit to string
    switch (suit) {
    case Clubs:    suit_str = "c"; break;
    case Diamonds: suit_str = "d"; break;
    case Hearts:   suit_str = "h"; break;
    case Spades:   suit_str = "s"; break;
    }

    return rank_str+suit_str;
}

Card::Card(Suit suit, Rank rank) :suit(suit),rank(rank)
{
}

Card::Suit Card::get_suit() const
{
    return suit;
}

Card::Rank Card::get_rank() const
{
    return rank;
}

std::vector<Card::Suit> Card::all_suits()
{
    std::vector<Suit> suits;
    for (int i = static_cast<int>(Clubs); i <= static_cast<int>(Suit::Spades); ++i) {
        suits.push_back(static_cast<Suit>(i));
    }
    return suits;
}

std::vector<Card::Rank> Card::all_ranks()
{
    std::vector<Rank> ranks;
    for (int i = static_cast<int>(Two); i <= static_cast<int>(Rank::Ace); ++i) {
        ranks.push_back(static_cast<Rank>(i));
    }
    return ranks;
}

