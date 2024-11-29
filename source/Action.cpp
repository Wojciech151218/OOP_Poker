//
// Created by wojciech on 11/6/24.
//

#include "../headers/Action.h"

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

