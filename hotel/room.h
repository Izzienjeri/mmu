#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
public:
    int roomNumber;
    std::string type;
    double pricePerNight;
    bool isAvailable;

    Room(int number, const std::string& type, double price, bool available);
    void displayDetails() const;
    void bookRoom();  // Handles booking logic
};

#endif
