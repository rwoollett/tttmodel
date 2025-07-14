#include "TicTacToe.h"

namespace TTTModel
{

  bool Validate::Game(const TTTModel::Game &o)
  {
    return !(o.userId.empty());
  }

  bool Validate::GameStart(const TTTModel::GameStart &o)
  {
    return !(o.gameId.empty());
  }

  bool Validate::GameUpdate(const TTTModel::GameUpdate &o)
  {
    return !(o.board.empty() ||
             o.result.empty() ||
             o.gameId.empty());
  }

  bool Validate::PlayerMove(const TTTModel::PlayerMove &o)
  {
    return ((o.player == 1 || o.player == 2) &&
            (o.moveCell > 0 && o.moveCell < 10) &&
            !(o.gameId.empty()));
  }

}