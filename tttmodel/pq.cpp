#include "pq.h"
#include <unordered_map>
#include "timestamp.h"

#ifdef NDEBUG
#define D(x)
#else
#define D(x) x
#endif

#ifdef LIBPQ_FOUND
namespace Model::PG
{
  std::unordered_map<std::string, int> mapFieldCols(PGresult *res, int nCols)
  {
    std::unordered_map<std::string, int> fieldColumns{};
    for (int i = 0; i < nCols; i++)
    {
      const char *field_name = PQfname(res, i);
      fieldColumns[std::string(field_name)] = i;
    }
    return fieldColumns;
  };

  auto const getStringFromResRowByKey = [](
                                            PGresult *res,
                                            int rowIndex,
                                            const std::unordered_map<std::string, int> &fieldColumns,
                                            const std::string &key) -> std::string
  {
    auto it = fieldColumns.find(key);
    if (it == fieldColumns.end())
      throw std::string("Field not matched for " + key);
    return std::string(PQgetvalue(res, rowIndex, fieldColumns.at(key)));
  };

  Model::Game Game::fromPGRes(PGresult *res, int nCols, int rowIndex)
  {
    Model::Game game{};
    try
    {
      auto fieldColumns = mapFieldCols(res, nCols);
      auto const getString = [res, rowIndex, &fieldColumns](const std::string &key)
      {
        return getStringFromResRowByKey(res, rowIndex, fieldColumns, key);
      };

      // D(std::cerr << "connected bool from pq: " << getString("connected") << std::endl;)
      game.id = getString("id");
      game.board = getString("board");
      game.userId = getString("userId");
      game.createdAt = getString("createdAt");
      auto tpOptCA = parseDate(getString("createdAt"));
      if (tpOptCA)
        game.tpCreatedAt = *tpOptCA;
    }
    catch (const std::string &e)
    {
      throw e;
    }
    catch (...)
    {
      throw "error in fromPQRes";
    }

    return game;
  }

  Model::PlayerMove PlayerMove::fromPGRes(PGresult *res, int nCols, int rowIndex)
  {

    Model::PlayerMove playerMove{};
    auto fieldColumns = mapFieldCols(res, nCols);
    auto const getString = [res, rowIndex, &fieldColumns](const std::string &key)
    {
      return getStringFromResRowByKey(res, rowIndex, fieldColumns, key);
    };

    try
    {
      playerMove.id = getString("id");
      playerMove.gameId = getString("gameId");
      playerMove.isOpponentStart = (getString("isOpponentStart") == "t");
      playerMove.allocated = (getString("allocated") == "t");
      playerMove.player = std::atoi(getString("player").c_str());
      playerMove.moveCell = std::atoi(getString("moveCell").c_str());
    }
    catch (const std::string &e)
    {
      throw e;
    }
    catch (...)
    {
      throw "error in fromConnectPQRes";
    }

    return playerMove;
  }

} // namespace Model::PG
#endif // LIBPQ_FOUND
