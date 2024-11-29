//
// Created by wojciech on 11/6/24.
//

#ifndef UTILS_H
#define UTILS_H
#include <unordered_map>

#include "vector"
#include "regex"
#include "../headers/GameState.h"
#define let const auto

inline std::vector<std::string> seprate_string_by_spaces(const std::string & str){
    std::regex whitespace("\\s+"); // Matches any whitespace
    std::sregex_token_iterator iter(str.begin(), str.end(), whitespace, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> words(iter, end);
    return words;
}


#endif //UTILS_H
