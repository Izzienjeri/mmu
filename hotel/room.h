#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class Room {
public:
    int roomNumber;
    std::string type;
    double pricePerNight;
    bool isAvailable;

    // Constructor to initialize Room with all parameters
    Room(int roomNumber, const std::string& type, double pricePerNight, bool isAvailable)
        : roomNumber(roomNumber), type(type), pricePerNight(pricePerNight), isAvailable(isAvailable) {}
};

// Function declarations
std::vector<Room> loadRoomsFromCSV(const std::string& filename);
void saveRoomsToCSV(const std::string& filename, const std::vector<Room>& rooms);

#endif // ROOM_H
