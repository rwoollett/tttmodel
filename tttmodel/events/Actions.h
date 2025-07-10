
#ifndef EVENT_TTT_ACTIONS_H
#define EVENT_TTT_ACTIONS_H

#include "Subjects.h"
#include <string>
#include <chrono>

namespace Events
{
  struct GameUpdateByIdEvent
  {
    Subject subject{Subject::GameUpdateById};
    std::string gameId;
    std::string board;
    std::string result;
    GameUpdateByIdEvent() = default;
  };

  struct GameCreateEvent
  {
    Subject subject{Subject::GameCreate};
    std::string gameId;
    std::string board;
    std::string createdAt;
    std::chrono::system_clock::time_point tpCreatedAt{};
    GameCreateEvent() = default;
  };

  struct PlayerMoveEvent
  {
    Subject subject{Subject::PlayerMove};
    std::string id;
    std::string gameId;
    int player;
    int moveCell;
    bool isOpponentStart;
    PlayerMoveEvent() = default;
  };

}
#endif // EVENT_TTT_ACTIONS_H
