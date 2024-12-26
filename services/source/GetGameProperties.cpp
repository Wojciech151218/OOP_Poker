//
// Created by wojciech on 12/15/24.
//

#include "../headers/GetGameProperties.h"

GetGameProperties::GetGameProperties(GameState& game_state):game_state(game_state){

}

crow::json::wvalue GetGameProperties::getJsonResponse() const{
    crow::json::wvalue response;

    response["playerNumber"] = game_state.get_players().size();
    response["smallBet"] = 50;//todo

    return  response;
}
