#include "room.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<Room> loadRoomsFromCSV(const std::string& filename) {
    std::vector<Room> rooms;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return rooms;
    }

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        // Read data
        std::getline(iss, token, ',');
        int roomNumber = std::stoi(token);
        std::getline(iss, token, ',');
        std::string type = token;
        std::getline(iss, token, ',');
        double pricePerNight = std::stod(token);
        std::getline(iss, token, ',');
        bool isAvailable = token == "1";

        // Initialize room with the required parameters
        Room room(roomNumber, type, pricePerNight, isAvailable);

        rooms.push_back(room);
    }

    file.close();
    return rooms;
}


void saveRoomsToCSV(const std::string& filename, const std::vector<Room>& rooms) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    // Write header
    file << "RoomNumber,Type,PricePerNight,IsAvailable\n";

    for (const auto& room : rooms) {
        file << room.roomNumber << "," 
             << room.type << "," 
             << room.pricePerNight << "," 
             << (room.isAvailable ? "1" : "0") << "\n";
    }

    file.close();
}
