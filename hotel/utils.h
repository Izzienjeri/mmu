#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include "room.h"

// Utility function declarations
bool isDateValid(const std::string& date);
bool isDateInPast(const std::string& date);
bool isEndDateAfterStartDate(const std::string& startDate, const std::string& endDate);
std::string toLower(const std::string& str);
bool isRoomNumberValid(int roomNumber, const std::vector<Room>& rooms);
void displayAvailableRooms(const std::vector<Room>& rooms);

#endif // UTILS_H
