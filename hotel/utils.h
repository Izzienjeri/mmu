#ifndef UTILS_H
#define UTILS_H

#include <string>

// Utility function declarations
bool isDateValid(const std::string& date);
bool isDateInPast(const std::string& date);
bool isEndDateAfterStartDate(const std::string& startDate, const std::string& endDate);
std::string toLower(const std::string& str);

#endif // UTILS_H
