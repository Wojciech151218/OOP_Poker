//
// Created by wojciech on 11/6/24.
//

#ifndef ACTION_H
#define ACTION_H
#include <string>

#include "cstddef"


class Action {
public:
    enum ActionType{CheckCall,BetRaise,Fold};

    static ActionType from_string(const std::string& string);
    static std::string from_action(const  ActionType& action);
    Action(size_t bet_size,ActionType action);
    Action();
    ActionType get_action_type() const;
    size_t get_bet_size() const;

private:
    ActionType action_type;
    size_t bet_size;

};



#endif //ACTION_H
