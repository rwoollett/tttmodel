#include "TicTacToe.h"

namespace Model
{

  bool Validate::Game(const Model::Game &o)
  {
    return !(o.userId.empty());
  }

  bool Validate::GameStart(const Model::GameStart &o)
  {
    return !(o.gameId.empty());
  }

  bool Validate::PlayerMove(const Model::PlayerMove &o)
  {
    return ((o.player == 1 || o.player == 2) &&
            (o.moveCell > 0 && o.moveCell < 10) &&
            !(o.gameId.empty()));
  }

}