// Created by wojciech on 11/6/24.

#include "../headers/UserInterface.h"

#include <iostream>
#include <string>
#include <vector>
#include "../headers/Action.h"
#include "../headers/utils.h"

UserInterface::UserInterface(const std::vector<Player> & players,const GameProperties & game_properties)
    :game_state(GameState(players,game_properties))
{
}

void UserInterface::console_ui_loop()
{
    while (true)
    {
        game_state.print_state();
        std::string user_input;
        std::getline(std::cin, user_input);

        // Assuming separate_string_by_spaces is a function that splits a string by spaces and returns a vector of strings
        std::vector<std::string> input = seprate_string_by_spaces(user_input);

        if (input.empty()) continue; // Skip if input is empty

        Action action;
        bool not_proper_input = false;

        if (input[0] == "check") {
            action = Action(0, Action::CheckCall);
        }
        else if (input[0] == "bet" && input.size() > 1) {
            try {
                action = Action(std::stoi(input[1]), Action::BetRaise);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid amount provided for bet.\n";
                not_proper_input = true;
            }
        }
        else if (input[0] == "fold") {
            action = Action(0, Action::Fold);
        }
        else {
            not_proper_input = true;
            std::cerr << "Invalid command.\n";
        }

        if (not_proper_input) continue;

        game_state.process_action(action);

    }

}
