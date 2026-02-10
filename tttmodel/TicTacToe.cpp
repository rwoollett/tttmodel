#include "TicTacToe.h"

namespace TTTModel
{
  inline bool isAllDigits(const std::string &s)
  {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(), ::isdigit);
  }

  bool Validate::Game(const TTTModel::Game &o)
  {
    return isAllDigits(o.userId);
  }

  bool Validate::GameStart(const TTTModel::GameStart &o)
  {
    return isAllDigits(o.gameId);
  }

  bool Validate::GameUpdate(const TTTModel::GameUpdate &o)
  {
    return isAllDigits(o.gameId) &&
           !(o.board.empty() || o.result.empty());
  }

  bool Validate::PlayerMove(const TTTModel::PlayerMove &o)
  {
    return ((o.player == 1 || o.player == 2) &&
            (o.moveCell >= 0 && o.moveCell < 9) &&
            isAllDigits(o.gameId)) ||
           (o.isOpponentStart == true && o.moveCell == -1);
  }

}