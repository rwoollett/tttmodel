#pragma once

#include "ClientCS.h"

#ifdef LIBPQ_FOUND
#include <libpq-fe.h>
namespace Model::PG
{
  namespace ClientCS
  {
    Model::ClientCS fromPGRes(PGresult *res, int nCols, int rowIndex = 0);
  }

  namespace ClientConnectCS
  {
    Model::ClientConnectCS fromPGRes(PGresult *res, int nCols, int rowIndex = 0);
  }

  namespace ClientDisconnectCS
  {
    Model::ClientDisconnectCS fromPGRes(PGresult * res, int nCols, int rowIndex = 0);
  }

} // namespace Model
#endif //LIBPQ_FOUND
