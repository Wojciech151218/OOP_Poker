//
// Created by wojciech on 12/15/24.
//

#ifndef POSTACTION_H
#define POSTACTION_H
#include <GameState.h>
#include <crow/http_response.h>


class PostAction {
	GameState & game_state;
	public:
	PostAction(GameState & game_state);
	crow::response handle_post(const crow::request& request);


};



#endif //POSTACTION_H
