#include <iostream>
#include <PokerAI.h>

#include "crow.h"
#include "headers/UserInterface.h"
#include "headers/utils.h"
#include "services/headers/GetGameProperties.h"
#include "services/headers/GetStateRequest.h"
#include "services/headers/PostAction.h"

int main()
{
    crow::SimpleApp app;

    std::vector players = { Player(100),Player(100),Player(100),
        Player(100),Player(100)};
    auto game_properties = GameProperties{5,10,5};
    GameState game_state(players,game_properties);

    GetStateRequest get_state_request(game_state);
    GetGameProperties get_game_properties(game_state);
    PostAction post_action(game_state);
    PokerAI poker_ai(game_state);


    // Define a GET endpoint to return the game state
    CROW_ROUTE(app, "/api/game-state/<int>").methods("GET"_method)(
    [ &get_state_request](int player_id) {
        return get_state_request.getJsonResponse(player_id);
    });
    CROW_ROUTE(app, "/api/game-state").methods("POST"_method)([&post_action]
        (const crow::request& request) {
        return post_action.handle_post(request);
    });
    CROW_ROUTE(app, "/api/game-properties").methods("GET"_method)([&get_game_properties]() {
        return get_game_properties.getJsonResponse();
    });
    CROW_ROUTE(app, "/api/fetch-move/<int>").methods("GET"_method)([&poker_ai,&game_state]
        (int player_id) {
        poker_ai.random_move();
        crow::json::wvalue response;
        response["fetched"] = game_state.get_current_player_index() == player_id;
        return response;
    });



    // Start the Crow server on localhost:8080
    app.port(8080).multithreaded().run();

}
