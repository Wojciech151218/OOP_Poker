//
// Created by wojciech on 12/19/24.
//

#include "../headers/PokerAI.h"

#include <iostream>
#include <thread>
#include <utils.h>
#include "Action.h"

PokerAI::PokerAI(GameState& game_state)
:game_state(game_state){
}

void PokerAI::random_move(){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    let action = game_state.make_random_action();
    std::cout<<"random move made "<< Action::from_action(action)<<"\n";
}
