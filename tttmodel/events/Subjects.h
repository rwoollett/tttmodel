
#ifndef EVENT_SUBJECTS_H
#define EVENT_SUBJECTS_H

#include <string>
#include <map>
#include <string_view>

namespace Events
{
  
  enum class Subject
  {
    Invalid = -1,
    GameUpdateById,
    GameCreate,
    PlayerMove
  };

  static const std::map<Subject, std::string_view> SubjectNames = {
      {Subject::GameUpdateById, "game_Update"},
      {Subject::GameCreate, "game_Create"},
      {Subject::PlayerMove, "player_Move"}};

  static const std::map<std::string_view, Subject> SubjectFromNames = {
      {"game_Update", Subject::GameUpdateById},
      {"game_Create", Subject::GameCreate},
      {"player_Move", Subject::PlayerMove}};

}
#endif // EVENT_SUBJECTS_H
