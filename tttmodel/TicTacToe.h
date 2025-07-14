
#ifndef MODEL_TTT_H
#define MODEL_TTT_H

#include <string>
#include <map>
#include <set>
#include <algorithm> //for_each
#include <iostream>
#include <chrono>

namespace TTTModel
{

  // Define a struct to encapsulate Game table insert, update and query
  struct Game
  {
    std::string id;
    std::string userId;
    std::string board;
    std::string createdAt;
    std::chrono::system_clock::time_point tpCreatedAt{};

    Game() = default;
  };

  struct GameStart
  {
    std::string gameId;
    GameStart() = default;
  };

  struct GameUpdate
  {
    std::string gameId;
    std::string board;
    std::string result;
    GameUpdate() = default;
  };

  // Define a struct to encapsulate PlayerMove table insert, update and query
  struct PlayerMove
  {
    std::string id;
    std::string gameId;
    int player;
    int moveCell;
    bool isOpponentStart;
    bool allocated;
    std::string board;

    PlayerMove() = default;
  };

  namespace Validate
  {
    bool Game(const TTTModel::Game &o);
    bool GameStart(const TTTModel::GameStart &o);
    bool GameUpdate(const TTTModel::GameUpdate &o);
    bool PlayerMove(const TTTModel::PlayerMove &o);
  }
  
}
#endif // MODEL_TTT_H
