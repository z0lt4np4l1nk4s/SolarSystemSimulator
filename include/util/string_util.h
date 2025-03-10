#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iomanip>
#include <sstream>

std::string toStringWithPrecision(double value, int precision = 2)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
}

#endif