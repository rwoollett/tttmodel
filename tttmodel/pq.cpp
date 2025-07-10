#include "ClientCS.h"
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

  Model::ClientCS ClientCS::fromPGRes(PGresult *res, int nCols, int rowIndex)
  {
    Model::ClientCS clientCS{};
    auto fieldColumns = mapFieldCols(res, nCols);
    auto const getString = [res, rowIndex, &fieldColumns](const std::string &key)
    {
      return getStringFromResRowByKey(res, rowIndex, fieldColumns, key);
    };

    try
    {
      // D(std::cerr << "connected bool from pq: " << getString("connected") << std::endl;)
      clientCS.name = getString("name");
      clientCS.host = getString("host");
      clientCS.ip = getString("ip");
      clientCS.connected = (getString("connected") == "t");
      clientCS.processId = getString("processId");
      clientCS.connectedAt = getString("connectedAt");
      clientCS.disconnectedAt = getString("disconnectedAt");
      auto tpOptCA = parseDate(getString("connectedAt"));
      auto tpOptDA = parseDate(getString("disconnectedAt"));
      if (tpOptCA)
        clientCS.tpConnectedAt = *tpOptCA;
      if (tpOptDA)
        clientCS.tpDisconnectedAt = *tpOptDA;

      clientCS.parentId = std::atoi(getString("parentId").c_str());
      clientCS.clientIp = getString("clientIp");
    }
    catch (const std::string &e)
    {
      throw e;
    }
    catch (...)
    {
      throw "error in fromPQRes";
    }

    return clientCS;
  }

  Model::ClientConnectCS ClientConnectCS::fromPGRes(PGresult *res, int nCols, int rowIndex)
  {

    Model::ClientConnectCS clientConnectCS{};
    auto fieldColumns = mapFieldCols(res, nCols);
    auto const getString = [res, rowIndex, &fieldColumns](const std::string &key)
    {
      return getStringFromResRowByKey(res, rowIndex, fieldColumns, key);
    };

    try
    {
      clientConnectCS.sourceIp = getString("sourceIp");
      clientConnectCS.connected = (getString("connected") == "t");
      clientConnectCS.processId = getString("processId");
      clientConnectCS.connectedAt = getString("connectedAt");
      auto tpOptCA = parseDate(getString("connectedAt"));
      if (tpOptCA)
        clientConnectCS.tpConnectedAt = *tpOptCA;
    }
    catch (const std::string &e)
    {
      throw e;
    }
    catch (...)
    {
      throw "error in fromConnectPQRes";
    }

    return clientConnectCS;
  }
  
  Model::ClientDisconnectCS ClientDisconnectCS::fromPGRes(PGresult *res, int nCols, int rowIndex)
  {

    Model::ClientDisconnectCS clientDisconnectCS{};
    auto fieldColumns = mapFieldCols(res, nCols);
    auto const getString = [res, rowIndex, &fieldColumns](const std::string &key)
    {
      return getStringFromResRowByKey(res, rowIndex, fieldColumns, key);
    };

    try
    {
      clientDisconnectCS.sourceIp = getString("sourceIp");
      clientDisconnectCS.connected = (getString("connected") == "t");
      clientDisconnectCS.disconnectedAt = getString("disconnectedAt");
      auto tpOptCA = parseDate(getString("disconnectedAt"));
      if (tpOptCA)
        clientDisconnectCS.tpDisconnectedAt = *tpOptCA;
    }
    catch (const std::string &e)
    {
      throw e;
    }
    catch (...)
    {
      throw "error in fromConnectPQRes";
    }

    return clientDisconnectCS;
  }

} // namespace Model::PG
#endif // LIBPQ_FOUND
