#include "timestamp.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <string>
#include <iostream>

#ifdef NDEBUG
#define D(x)
#else
#define D(x) x
#endif

namespace Model
{

  constexpr auto FORMAT_DATE = "%Y-%m-%d %H:%M:%S";

  std::string formatDate(const std::chrono::system_clock::time_point &tp)
  {
    std::stringstream format;
    auto secondsChk = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
    if (secondsChk <= 0)
    {
      return ""; // Dont use the an ecpoch date/time string use empty string
    }

    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    auto duration = tp.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    // std::cerr << "seconds " << secondsChk << " " << seconds.count() << "\n";
    auto subseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - seconds).count();

    std::tm tm = *std::localtime(&t); // or std::gmtime(&t) for greenwich time

    format << std::put_time(&tm, FORMAT_DATE);
    format << '.' << std::setw(3) << std::setfill('0') << subseconds << "Z"; // milliseconds, ISO 8601

    return format.str();
  }

  std::optional<std::chrono::system_clock::time_point> parseDate(const std::string &isoDate)
  {
    if (isoDate.empty())
    {
      return std::nullopt;
    }

    D(std::cerr << "parseDate isodate : " << isoDate << std::endl;)
    std::tm tm = {};
    size_t dot_pos = isoDate.find('.');
    int milliseconds = 0;

    std::string datetime_part = isoDate.substr(0, dot_pos);
    std::istringstream ss(datetime_part);
    ss >> std::get_time(&tm, FORMAT_DATE);
    if (ss.fail())
    {
      throw std::string("failed to parse date");
    }

    if (dot_pos != std::string::npos)
    {
      size_t ms_end = isoDate.find_first_not_of("0123456789", dot_pos + 1);
      std::string ms_str = isoDate.substr(dot_pos + 1, ms_end - dot_pos - 1);
      if (!ms_str.empty())
      {
        milliseconds = std::stoi(ms_str);
      }
    }

    std::time_t time_sec = std::mktime(&tm);
    auto tp = std::chrono::system_clock::from_time_t(time_sec) + std::chrono::milliseconds(milliseconds);
    return tp;
  };

  std::chrono::system_clock::time_point timeNow()
  {
    return std::chrono::system_clock::now();
  }

}