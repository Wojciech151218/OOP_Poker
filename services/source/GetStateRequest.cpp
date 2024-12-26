//
// Created by wojciech on 12/9/24.
//

#include "../headers/GetStateRequest.h"

#include <utils.h>
GetStateRequest::GetStateRequest(GameState &game_state) :game_state(game_state){}
crow::json::wvalue GetStateRequest::getJsonResponse(int player_id) const {
    crow::json::wvalue response;

    // Get the current player's ID
    if(player_id<0 || player_id>= game_state.get_players().size()){
        crow::json::wvalue errorResponse;
        errorResponse["error"] = "Invalid player ID.";
        return errorResponse;
    }

    // Collect pocket cards
    std::vector<crow::json::wvalue> pocket_cards_json;
    for (const auto& card : game_state.get_players()[player_id].get_pocket_cards()) {
        pocket_cards_json.emplace_back(card.to_string());
    }

    // Collect common cards (table cards)
    std::vector<crow::json::wvalue> common_cards_json;
    for (const auto& card : game_state.get_table()) {
        common_cards_json.emplace_back(card.to_string());
    }

    // Collect bankrolls for all players
    std::vector<crow::json::wvalue> player_bank_rolls_json;
    for (const auto& player : game_state.get_players()) {
        player_bank_rolls_json.emplace_back(player.get_bank_roll());
    }
    std::vector<crow::json::wvalue> player_bets_json;
    for(let bet : game_state.get_player_bets()){
        player_bets_json.emplace_back(bet);
    }

    // Populate the JSON response
    response["currentPlayerId"] = game_state.get_current_player_index();
    response["commonCards"] = std::move(common_cards_json);
    response["pocketCards"] = std::move(pocket_cards_json);
    response["playerBankrolls"] = std::move(player_bank_rolls_json);
    response["pot"] = game_state.get_pot();
    response["toCall"] = game_state.get_current_bet();
    response["playerBets"] = std::move(player_bets_json);
    response["playerStatus"] = Player::status_to_string( game_state.get_current_player().get_status());

    return response;
}

