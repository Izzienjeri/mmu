#include "utils.h"
#include <cctype>
#include <ctime>

// Utility function definitions

bool isDateValid(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return false;
        }
    }
    return true;
}

bool isDateInPast(const std::string& date) {
    // Convert string date to time_t for comparison
    struct tm tm = {0};
    strptime(date.c_str(), "%Y-%m-%d", &tm);
    time_t inputDate = mktime(&tm);

    // Get current date
    time_t now = time(0);
    return inputDate < now;
}

bool isEndDateAfterStartDate(const std::string& startDate, const std::string& endDate) {
    struct tm tmStart = {0}, tmEnd = {0};
    strptime(startDate.c_str(), "%Y-%m-%d", &tmStart);
    strptime(endDate.c_str(), "%Y-%m-%d", &tmEnd);
    
    time_t start = mktime(&tmStart);
    time_t end = mktime(&tmEnd);
    
    return difftime(end, start) > 0;
}

std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

bool isRoomNumberValid(int roomNumber, const std::vector<Room>& rooms) {
    for (const auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            return false; // Room number already exists
        }
    }
    return true; // Room number is valid
}

void displayAvailableRooms(const std::vector<Room>& rooms) {
    std::cout << "Available Rooms:\n";
    for (const auto& room : rooms) {
        if (room.isAvailable) {
            std::cout << "Room Number: " << room.roomNumber 
                      << ", Type: " << room.type 
                      << ", Price: Ksh " << room.pricePerNight 
                      << "\n";
        }
    }
}

