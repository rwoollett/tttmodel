#pragma once

#include "Actions.h"
#include "../timestamp.h"
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace TTTEvents
{

  inline void to_json(json &jsonOut, GameUpdateByIdEvent const &value)
  {
    json obj;
    obj["gameId"] = value.gameId;
    obj["board"] = value.board;
    obj["result"] = value.result;
    jsonOut["payload"] = obj;
    if (value.subject != Subject::GameUpdateById)
    {
      throw std::string("GameUpdateByIdEvent::to_json - Subject should be GameUpdateById");
    }
    jsonOut["subject"] = SubjectNames.at(value.subject);
  }

  inline void from_json(json const &jsonIn, GameUpdateByIdEvent &value)
  {
    json obj = jsonIn.at("payload");
    std::string subject;
    jsonIn.at("subject").get_to(subject);
    value.subject = SubjectFromNames.at(subject);
    obj.at("gameId").get_to(value.gameId);
    obj.at("board").get_to(value.board);
    obj.at("result").get_to(value.result);
  };

  inline void to_json(json &jsonOut, GameCreateEvent const &value)
  {
    json obj;
    obj["gameId"] = value.gameId;
    obj["board"] = value.board;
    obj["createdAt"] = TTTModel::formatDate(value.tpCreatedAt);
    jsonOut["payload"] = obj;
    if (value.subject != Subject::GameCreate)
    {
      throw std::string("GameCreateEvent::to_jsonn - Subject should be GameCreate");
    }
    jsonOut["subject"] = SubjectNames.at(value.subject);
  }

  inline void from_json(json const &jsonIn, GameCreateEvent &value)
  {
    json obj = jsonIn.at("payload");
    std::string subject;
    jsonIn.at("subject").get_to(subject);
    value.subject = SubjectFromNames.at(subject);
    obj.at("gameId").get_to(value.gameId);
    obj.at("board").get_to(value.board);
    auto tpOptCA = parseDate(value.createdAt);
    if (tpOptCA)
      value.tpCreatedAt = *tpOptCA;
  };

  inline void to_json(json &jsonOut, PlayerMoveEvent const &value)
  {
    json obj;
    obj["gameId"] = value.gameId;
    obj["board"] = value.board;
    obj["id"] = value.id;
    obj["player"] = value.player;
    obj["moveCell"] = value.moveCell;
    obj["isOpponentStart"] = value.isOpponentStart;
    jsonOut["payload"] = obj;
    if (value.subject != Subject::PlayerMove)
    {
      throw std::string("PlayerMoveEvent::to_json - Subject should be PlayerMove");
    }
    jsonOut["subject"] = SubjectNames.at(value.subject);
  }

  inline void from_json(json const &jsonIn, PlayerMoveEvent &value)
  {
    json obj = jsonIn.at("payload");
    std::string subject;
    jsonIn.at("subject").get_to(subject);
    value.subject = SubjectFromNames.at(subject);
    obj.at("gameId").get_to(value.gameId);
    obj.at("id").get_to(value.id);
    obj.at("player").get_to(value.player);
    obj.at("moveCell").get_to(value.moveCell);
    obj.at("isOpponentStart").get_to(value.isOpponentStart);
    if (obj.contains("board"))
    {
      obj.at("board").get_to(value.board);
    }
  };

} // namespace Events
