#pragma once

#include "TicTacToe.h"

#ifdef LIBPQ_FOUND
#include <libpq-fe.h>
namespace Model::PG
{
  namespace Game
  {
    Model::Game fromPGRes(PGresult *res, int nCols, int rowIndex = 0);
  }

  namespace PlayerMove
  {
    Model::PlayerMove fromPGRes(PGresult *res, int nCols, int rowIndex = 0);
  }


} // namespace Model
#endif //LIBPQ_FOUND
