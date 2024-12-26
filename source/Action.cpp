//
// Created by wojciech on 11/6/24.
//

#include "../headers/Action.h"

#include <iostream>
#include <map>
#include <utils.h>

Action::ActionType Action::from_string(const std::string& string){
    std::map<std::string,ActionType> map =
        {{"fold",Fold},{"call",CheckCall},{"bet",BetRaise} };
    let result = map.find(string);
    if(result == map.end()){
        std::cerr<<"unrecognized action type\n";
        return Fold;
    }
    return result->second;
}

std::string Action::from_action(const ActionType& action){
    switch (action){
    case Fold:
        return "fold";
    case CheckCall:
        return  "check call";
    case BetRaise:
        return "bet raise";
    }
}


Action::Action(size_t bet_size, ActionType action):bet_size(bet_size),action_type(action)
{

}

Action::Action():bet_size(0),action_type(Fold)
{

}

Action::ActionType Action::get_action_type() const
{
    return action_type;
}

size_t Action::get_bet_size() const
{
    return bet_size;
}

