//
// Created by wojciech on 12/28/24.
//

#ifndef GETGAMERESULT_H
#define GETGAMERESULT_H
#include <GameState.h>
#include <crow/json.h>

class GetGameResult {
  GameState & game_state;
public:
  GetGameResult(GameState & game_state);
  crow::json::wvalue getJsonResponse() const ;

};



#endif //GETGAMERESULT_H
