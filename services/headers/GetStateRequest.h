//
// Created by wojciech on 12/9/24.
//

#ifndef GETSTATEREQUEST_H
#define GETSTATEREQUEST_H

#include "crow.h"
#include <vector>

#include <GameState.h>

class GetStateRequest {
public:
  // Constructor
  GetStateRequest(GameState &game_state);

  // Method to fetch JSON data
  crow::json::wvalue getJsonResponse(int player_id) const;

private:
  GameState & game_state;
};

#endif //GETSTATEREQUEST_H
