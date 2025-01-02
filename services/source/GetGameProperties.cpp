//
// Created by wojciech on 12/15/24.
//

#include "../headers/GetGameProperties.h"



GetGameProperties::GetGameProperties(GameProperties &game_properties):game_properties(game_properties) {}
crow::json::wvalue GetGameProperties::getJsonResponse() const{
    crow::json::wvalue response;

    response["playerNumber"] = game_properties.player_number;
    response["smallBet"] = game_properties.small_bet;
    response["bigBet"] = game_properties.big_bet;



    return  response;
}
