#include "TicTacToe.h"

namespace TTTModel
{
  inline bool isAllDigits(const std::string &s)
  {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(), ::isdigit);
  }

  inline bool isAllAlnum(const std::string &s)
  {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(), ::isalnum);
  }

  inline bool isAllAlnumUnderscore(const std::string &s)
  {
    return !s.empty() &&
           std::all_of(s.begin(), s.end(),
                       [](unsigned char c)
                       {
                         return std::isalnum(c) || c == '_';
                       });
  }

  bool Validate::GameCreate(const TTTModel::GameCreate &o)
  {
    return isAllAlnumUnderscore(o.userId);
  }

  bool Validate::GameStart(const TTTModel::GameStart &o)
  {
    return isAllDigits(o.gameId) && isAllAlnumUnderscore(o.userId);
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
            isAllDigits(o.gameId) && isAllAlnumUnderscore(o.userId)) ||
           (o.isOpponentStart == true && o.moveCell == -1);
  }

}