//
// Created by wojciech on 12/15/24.
//

#ifndef GETGAMEPROPERTIES_H
#define GETGAMEPROPERTIES_H
#include <GameState.h>
#include <crow/json.h>


class GetGameProperties {


        GameProperties & game_properties;
public:
        // Constructor
        GetGameProperties(GameProperties &game_properties);

        // Method to fetch JSON data
        crow::json::wvalue getJsonResponse() const;

};



#endif //GETGAMEPROPERTIES_H
