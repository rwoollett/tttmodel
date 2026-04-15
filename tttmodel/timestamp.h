#pragma once
#include <chrono>
#include <ctime>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>

namespace Timestamp {

inline std::string formatDate(const std::chrono::system_clock::time_point& tp)
{
    auto secondsChk = std::chrono::duration_cast<std::chrono::seconds>(tp.time_since_epoch()).count();
    if (secondsChk <= 0)
        return "";

    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    std::tm tm {};
    gmtime_r(&t, &tm);  // UTC, thread‑safe

    auto duration = tp.time_since_epoch();
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto subseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - seconds).count();

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    oss << '.' << std::setw(3) << std::setfill('0') << subseconds << "Z";

    return oss.str();
}

inline std::optional<std::chrono::system_clock::time_point>
parseDate(const std::string& isoDate)
{
    if (isoDate.empty())
        return std::nullopt;

    std::tm tm {};
    int milliseconds = 0;

    size_t dot_pos = isoDate.find('.');
    std::string datetime_part = isoDate.substr(0, dot_pos);

    std::istringstream ss(datetime_part);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail())
        throw std::string("failed to parse date");

    if (dot_pos != std::string::npos)
    {
        size_t ms_end = isoDate.find_first_not_of("0123456789", dot_pos + 1);
        std::string ms_str = isoDate.substr(dot_pos + 1, ms_end - dot_pos - 1);
        if (!ms_str.empty())
            milliseconds = std::stoi(ms_str);
    }

    time_t utc_seconds = timegm(&tm);  // UTC, thread‑safe

    return std::chrono::system_clock::from_time_t(utc_seconds)
         + std::chrono::milliseconds(milliseconds);
}

inline std::chrono::system_clock::time_point timeNow()
{
    return std::chrono::system_clock::now();
}

} // namespace TTTModel
