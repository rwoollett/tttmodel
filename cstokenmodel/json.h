#pragma once

#include "ClientCS.h"
#include "timestamp.h"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Model
{

  inline void to_json(json &jsonOut, ClientCS const &value)
  {
    jsonOut["name"] = value.name;
    jsonOut["host"] = value.host;
    jsonOut["ip"] = value.ip;
    jsonOut["connected"] = value.connected;
    jsonOut["processId"] = value.processId;
    jsonOut["connectedAt"] = formatDate(value.tpConnectedAt);
    jsonOut["disconnectedAt"] = formatDate(value.tpDisconnectedAt);
    jsonOut["parentId"] = value.parentId;
    jsonOut["clientIp"] = value.clientIp;
    json parent;
    parent["id"] = value.parentId;
    parent["clientIp"] = value.clientIp;
    jsonOut["requestParent"] = parent;
  }

  inline void from_json(json const &jsonIn, ClientCS &value)
  {
    jsonIn.at("name").get_to(value.name);                     //  clientCS.name = getString("name");
    jsonIn.at("host").get_to(value.host);                     // = getString("host");
    jsonIn.at("ip").get_to(value.ip);                         // = getString("ip");
    jsonIn.at("connected").get_to(value.connected);           // = getString("connected").get<bool>();
    jsonIn.at("processId").get_to(value.processId);           //= getString("processId");
    jsonIn.at("connectedAt").get_to(value.connectedAt);       //= getString("connectedAt");
    jsonIn.at("disconnectedAt").get_to(value.disconnectedAt); //= getString("disconnectedAt");
    auto tpOptCA = parseDate(value.connectedAt);
    auto tpOptDA = parseDate(value.disconnectedAt);
    if (tpOptCA)
      value.tpConnectedAt = *tpOptCA;
    if (tpOptDA)
      value.tpDisconnectedAt = *tpOptDA;
  };

  inline void to_json(json &jsonOut, ClientConnectCS const &value)
  {
    jsonOut["sourceIp"] = value.sourceIp;
    jsonOut["connected"] = value.connected;
    jsonOut["processId"] = value.processId;
    jsonOut["connectedAt"] = formatDate(value.tpConnectedAt);
  }

  inline void from_json(json const &jsonIn, ClientConnectCS &value)
  {
    jsonIn.at("sourceIp").get_to(value.sourceIp);
    jsonIn.at("processId").get_to(value.processId);
    // If connected at date is present from the response of api request
    if (jsonIn.contains("connectedAt"))
    {
      jsonIn.at("connectedAt").get_to(value.connectedAt);
      auto tpOptCA = parseDate(value.connectedAt);
      if (tpOptCA)
        value.tpConnectedAt = *tpOptCA;
    }
  }

  inline void to_json(json &jsonOut, ClientDisconnectCS const &value)
  {
    jsonOut["sourceIp"] = value.sourceIp;
    jsonOut["connected"] = value.connected;
    jsonOut["disconnectedAt"] = formatDate(value.tpDisconnectedAt);
  }

  inline void from_json(json const &jsonIn, ClientDisconnectCS &value)
  {
    jsonIn.at("sourceIp").get_to(value.sourceIp);
    if (jsonIn.contains("disconnectedAt"))
    {
      jsonIn.at("disconnectedAt").get_to(value.disconnectedAt);
      auto tpOpt = parseDate(value.disconnectedAt);
      if (tpOpt)
        value.tpDisconnectedAt = *tpOpt;
    }
  }

  inline void to_json(json &jsonOut, CSTokenRequest const &value)
  {
    jsonOut["sourceIp"] = value.sourceIp;
    jsonOut["originalIp"] = value.originalIp;
    jsonOut["parentIp"] = value.parentIp;
    jsonOut["relayed"] = value.relayed;
  }

  inline void from_json(json const &jsonIn, CSTokenRequest &value)
  {
    jsonIn.at("sourceIp").get_to(value.sourceIp);
    jsonIn.at("originalIp").get_to(value.originalIp);
    jsonIn.at("parentIp").get_to(value.parentIp);
    jsonIn.at("relayed").get_to(value.relayed);
  }

  inline void to_json(json &jsonOut, CSTokenAcquire const &value)
  {
    jsonOut["sourceIp"] = value.sourceIp;
    jsonOut["ip"] = value.ip;
  }

  inline void from_json(json const &jsonIn, CSTokenAcquire &value)
  {
    jsonIn.at("sourceIp").get_to(value.sourceIp);
    jsonIn.at("ip").get_to(value.ip);
  }

} // namespace Model
