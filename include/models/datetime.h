#ifndef DATETIME_H
#define DATETIME_H

#include <string>

class DateTime
{
public:
    DateTime();
    DateTime(int year, int month, int day);
    DateTime(int year, int month, int day, int hour, int minute, int second);

    static DateTime now();
    static DateTime today();
    void addDays(int days);
    float yearsSince(const DateTime &reference) const;
    void print() const;
    std::string toString() const;

private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

#endif