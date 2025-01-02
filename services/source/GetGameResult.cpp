//
// Created by wojciech on 12/28/24.
//

#include "../services/headers/GetGameResult.h"

#include <utils.h>
GetGameResult::GetGameResult(GameState &game_state) : game_state(game_state) {}
crow::json::wvalue GetGameResult::getJsonResponse() const {
  crow::json::wvalue response;

  // Retrieve the result of the current game round
  let round_result = game_state.get_round_result();

  if (round_result.has_value()) {
    // Container for winners' pocket cards as strings
    auto winners_pocket_cards = std::vector<std::vector<std::string>>();
    auto player_names = std::vector<std::string>();

    auto common_cards = std::vector<std::string>();

    // Process each winner's pocket cards
    for (let &winner : round_result->get_winners()) {
      auto pocket_cards_as_strings = std::vector<std::string>();
      player_names.emplace_back(winner.get_player_name());
      for (let &card : winner.get_pocket_cards()) {
        pocket_cards_as_strings.emplace_back(card.to_string());
      }

      winners_pocket_cards.emplace_back(std::move(pocket_cards_as_strings));
    }

    // Process the table's common cards
    for (let &card : round_result->get_table()) {
      common_cards.emplace_back(card.to_string());
    }

    // Populate the response with winners' cards and common cards
    response["winnersCards"] = winners_pocket_cards;
    response["commonCards"] = common_cards;
    response["playerNames"] = player_names;
  } else {
    // Indicate that the game is not finished
    response["notFinished"] = true;
  }

  return response;
}

