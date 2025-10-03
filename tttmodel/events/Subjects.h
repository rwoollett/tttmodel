
#ifndef EVENT_TTT_SUBJECTS_H
#define EVENT_TTT_SUBJECTS_H

#include <string>
#include <map>
#include <string_view>

namespace TTTEvents
{
  
  enum class Subject
  {
    Invalid = -1,
    GameUpdateById,
    GameCreate,
    PlayerMove
  };

  static const std::map<Subject, std::string_view> SubjectNames = {
      {Subject::GameUpdateById, "ttt_game_Update"},
      {Subject::GameCreate, "ttt_game_Create"},
      {Subject::PlayerMove, "ttt_player_Move"}};

  static const std::map<std::string_view, Subject> SubjectFromNames = {
      {"ttt_game_Update", Subject::GameUpdateById},
      {"ttt_game_Create", Subject::GameCreate},
      {"ttt_player_Move", Subject::PlayerMove}};

}
#endif // EVENT_TTT_SUBJECTS_H
