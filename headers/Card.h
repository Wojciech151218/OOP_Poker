//
// Created by wojciech on 11/6/24.
//

#ifndef CARD_H
#define CARD_H
#include <vector>


class Card {
public:
    enum Suit{Clubs,Diamonds,Hearts,Spades};
    enum Rank{Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King,Ace};
    static std::vector<Suit> all_suits();
    static std::vector<Rank> all_ranks();

    void print() const;
    Card(Suit suit, Rank rank);
    Suit get_suit() const;
    Rank get_rank() const;
private:
    Suit suit;
    Rank rank;
};



#endif //CARD_H
