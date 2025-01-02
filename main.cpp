#include <iostream>
#include <PokerAI.h>

#include "crow.h"
#include "headers/UserInterface.h"
#include "headers/utils.h"
#include "services/headers/GetGameProperties.h"
#include "services/headers/GetGameResult.h"
#include "services/headers/GetStateRequest.h"
#include "services/headers/PostAction.h"

int main()
{
    crow::SimpleApp app;

    std::vector players = {
        //Player(100,"Witaliusz"),
        Player(100,"Sylwester"),
        Player(100,"Gniewomir"),
        Player(100, "Anna Maria"),
        Player(100,"Czestowojna")
    };
    auto game_properties = GameProperties{5,10,5,players.size()};
    GameState game_state(players,game_properties);

    GetStateRequest get_state_request(game_state);
    GetGameProperties get_game_properties(game_properties);
    PostAction post_action(game_state);
    GetGameResult get_game_result(game_state);
    PokerAI poker_ai(game_state);


    CROW_ROUTE(app, "/api/game-state/<int>").methods("GET"_method)(
    [&get_state_request](int player_id) {
        return get_state_request.getJsonResponse(player_id);
    });
    CROW_ROUTE(app, "/api/game-state/<int>").methods("POST"_method)(
        [&post_action,&get_state_request](const crow::request& request,int player_id) {
            post_action.handle_post(request);
            return get_state_request.getJsonResponse(player_id);


    });
    CROW_ROUTE(app, "/api/game-properties").methods("GET"_method)(
        [&get_game_properties]() {
        return get_game_properties.getJsonResponse();
    });
    CROW_ROUTE(app, "/api/fetch-move/<int>").methods("GET"_method)(
        [&poker_ai,&get_state_request](int player_id) {
        poker_ai.random_move();
        return get_state_request.getJsonResponse(player_id);
    });
    CROW_ROUTE(app, "/api/game-result").methods("GET"_method)(
            [&get_game_result]() {
            return get_game_result.getJsonResponse();
    });

    app.port(8080).multithreaded().run();

}
