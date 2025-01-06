#include "room.h"
#include <iostream>

Room::Room(int number, const std::string& type, double price, bool available)
    : roomNumber(number), type(type), pricePerNight(price), isAvailable(available) {}

void Room::displayDetails() const {
    std::cout << "Room " << roomNumber << " (" << type << "): Ksh " << pricePerNight 
              << "/night - " << (isAvailable ? "Available" : "Booked") << "\n";
}

void Room::bookRoom() {
    if (isAvailable) {
        isAvailable = false;
    } else {
        std::cout << "Room " << roomNumber << " is already booked.\n";
    }
}

