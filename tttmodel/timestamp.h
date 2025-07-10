#ifndef MODEL_TTT_TIMESTAMP_H
#define MODEL_TTT_TIMESTAMP_H

#include <string>
#include <sstream>
#include <chrono>
#include <optional>

namespace Model
{

  template <typename... Args>
  std::string sstr(Args &&...args)
  {
    std::ostringstream sstr;
    // fold expression
    (sstr << std::dec << ... << args);
    return sstr.str();
  }

  std::string formatDate(const std::chrono::system_clock::time_point &tp);
  std::optional<std::chrono::system_clock::time_point> parseDate(const std::string &isoDate);
  std::chrono::system_clock::time_point timeNow();

}

#endif // MODEL_TTT_TIMESTAMP_H