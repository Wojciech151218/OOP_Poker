//
// Created by wojciech on 11/6/24.
//

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "GameState.h"


class UserInterface {
public:
    UserInterface(const std::vector<Player> & players,const GameProperties & game_properties) ;
    void console_ui_loop();
private:
    Action get_action();
    GameState game_state;


};



#endif //USERINTERFACE_H
