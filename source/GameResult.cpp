//
// Created by wojciech on 12/28/24.
//
#include "../headers/GameResult.h"
GameResult::GameResult(const std::vector<Card> &table,
                       const std::vector<Player> &winners)
    : table(table), winners(winners) {}
std::vector<Player> GameResult::get_winners() const { return winners; }
std::vector<Card> GameResult::get_table() const {
  return table;
}