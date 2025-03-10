#include "models/datetime.h"
#include <ctime>
#include <iostream>

DateTime::DateTime()
    : year(1900), month(1), day(1), hour(0), minute(0), second(0) {}

DateTime::DateTime(int year, int month, int day)
    : year(year), month(month), day(day), hour(0), minute(0), second(0) {}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}

DateTime DateTime::now()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    return DateTime(localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
                    localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
}

DateTime DateTime::today()
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);

    return DateTime(localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday);
}

void DateTime::addDays(int days)
{
    std::tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day + days;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    std::mktime(&tm); // normalize the time
    year = tm.tm_year + 1900;
    month = tm.tm_mon + 1;
    day = tm.tm_mday;
    hour = tm.tm_hour;
    minute = tm.tm_min;
    second = tm.tm_sec;
}

float DateTime::yearsSince(const DateTime &reference) const
{
    std::tm refTime = {};
    refTime.tm_year = reference.year - 1900;
    refTime.tm_mon = reference.month - 1;
    refTime.tm_mday = reference.day;
    refTime.tm_hour = reference.hour;
    refTime.tm_min = reference.minute;
    refTime.tm_sec = reference.second;

    std::tm currTime = {};
    currTime.tm_year = this->year - 1900;
    currTime.tm_mon = this->month - 1;
    currTime.tm_mday = this->day;
    currTime.tm_hour = this->hour;
    currTime.tm_min = this->minute;
    currTime.tm_sec = this->second;

    // Convert to time_t (seconds since epoch)
    std::time_t refEpoch = std::mktime(&refTime);
    std::time_t currEpoch = std::mktime(&currTime);

    // Compute difference in seconds
    double secondsElapsed = std::difftime(currEpoch, refEpoch);

    // Convert to years (assuming 365.25 days per year)
    return secondsElapsed / (365.25 * 24 * 3600);
}

void DateTime::print() const
{
    std::cout << year << "-" << month << "-" << day << std::endl;
}

std::string DateTime::toString() const
{
    return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}
