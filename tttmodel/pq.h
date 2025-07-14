#pragma once

#include "TicTacToe.h"

#ifdef LIBPQ_FOUND
#include <libpq-fe.h>
namespace TTTModel::PG
{
  namespace Game
  {
    TTTModel::Game fromPGRes(PGresult *res, int nCols, int rowIndex = 0);
  }

  namespace PlayerMove
  {
    TTTModel::PlayerMove fromPGRes(PGresult *res, int nCols, int rowIndex = 0);
  }


} // namespace Model
#endif //LIBPQ_FOUND
