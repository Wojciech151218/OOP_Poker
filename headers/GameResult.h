//
// Created by wojciech on 12/28/24.
//

#ifndef GAMERESULT_H
#define GAMERESULT_H
#include <Card.h>
#include <Player.h>
class GameResult{
  std::vector<Card> table;
  std::vector<Player> winners;
public:
  GameResult(const std::vector<Card> & table, const std::vector<Player> & winners);
  std::vector<Player> get_winners() const;
  std::vector<Card> get_table() const;
};

#endif //GAMERESULT_H
