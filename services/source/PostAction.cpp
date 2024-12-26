//
// Created by wojciech on 12/15/24.
//

#include "../headers/PostAction.h"

#include <utils.h>
#include <crow/json.h>

PostAction::PostAction(GameState& game_state):game_state(game_state){
}

crow::response PostAction::handle_post(const crow::request& request){
    try {
        // Parse the JSON body from the POST request
        auto json_body = crow::json::load(request.body);
        if (!json_body) {
            return crow::response(400, "Invalid JSON data");
        }

        // Extract data from the JSON payload (example keys: "name", "age")
        std::string action_name = json_body["actionType"].s();
        size_t bet_size = json_body["betSize"].i();
        let action = Action(bet_size,Action::from_string(action_name));
        game_state.process_action(action);


        crow::json::wvalue responseJson;


        return crow::response(200, responseJson);
    } catch (const std::exception& e)
    {
        // Handle any exception and return error response
        return crow::response(500, std::string("Server Error: ") + e.what());
    }
}
