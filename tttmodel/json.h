#pragma once

#include "TicTacToe.h"
#include "timestamp.h"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Model
{

  inline void to_json(json &jsonOut, Game const &value)
  {
    jsonOut["id"] = value.id;
    jsonOut["userId"] = value.userId;
    jsonOut["board"] = value.board;
    jsonOut["createdAt"] = formatDate(value.tpCreatedAt);
  }

  inline void from_json(json const &jsonIn, Game &value)
  {
    jsonIn.at("userId").get_to(value.userId);
    if (jsonIn.contains("id"))
    {
      jsonIn.at("id").get_to(value.id);
    }
    if (jsonIn.contains("board"))
    {
      jsonIn.at("board").get_to(value.board);
    }
    if (jsonIn.contains("createdAt"))
    {
      jsonIn.at("createdAt").get_to(value.createdAt);
      auto tpOptCA = parseDate(value.createdAt);
      if (tpOptCA)
        value.tpCreatedAt = *tpOptCA;
    }
  };

  inline void to_json(json &jsonOut, GameStart const &value)
  {
    jsonOut["gameId"] = value.gameId;
  }

  inline void from_json(json const &jsonIn, GameStart &value)
  {
    jsonIn.at("gameId").get_to(value.gameId);
  };

  inline void to_json(json &jsonOut, PlayerMove const &value)
  {
    jsonOut["id"] = value.id;
    jsonOut["gameId"] = value.gameId;
    jsonOut["player"] = value.player;
    jsonOut["moveCell"] = value.moveCell;
    jsonOut["isOpponentStart"] = value.isOpponentStart;
    jsonOut["allocated"] = value.allocated;
  }

  inline void from_json(json const &jsonIn, PlayerMove &value)
  {
    if (jsonIn.contains("id"))
    {
      jsonIn.at("id").get_to(value.id);
    }
    jsonIn.at("gameId").get_to(value.gameId);
    jsonIn.at("player").get_to(value.player);
    jsonIn.at("moveCell").get_to(value.moveCell);
    jsonIn.at("isOpponentStart").get_to(value.isOpponentStart);
    if (jsonIn.contains("allocated"))
    {
      jsonIn.at("allocated").get_to(value.allocated);
    }
  }

} // namespace Model
