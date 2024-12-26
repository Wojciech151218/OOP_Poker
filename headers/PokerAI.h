//
// Created by wojciech on 12/19/24.
//

#ifndef POKERAI_H
#define POKERAI_H
#include <GameState.h>


class PokerAI {
    GameState & game_state;
public:
    PokerAI(GameState & game_state);
    void random_move();


};



#endif //POKERAI_H
