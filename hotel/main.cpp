#include <iostream>
#include <vector>
#include "room.h"
#include "booking.h"
#include "customer.h"
#include "utils.h"

void displayAvailableRooms(const std::vector<Room>& rooms) {
    std::cout << "Available Rooms:\n";
    for (const auto& room : rooms) {
        if (room.isAvailable) {
            room.displayDetails();
        }
    }
}

bool isRoomNumberValid(int roomNumber, const std::vector<Room>& rooms) {
    for (const auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            return false; // Room number already exists
        }
    }
    return true;
}

void makeBooking(std::vector<Room>& rooms, std::vector<Booking>& bookings, std::vector<Customer>& customers) {
    int roomNumber;
    std::string customerName, startDate, endDate;

    std::cout << "Enter room number to book: ";
    std::cin >> roomNumber;
    std::cout << "Enter customer name: ";
    std::cin >> customerName;
    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::cin >> startDate;
    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::cin >> endDate;

    bool roomAvailable = false;
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && room.isAvailable) {
            roomAvailable = true;
            room.isAvailable = false;
            break;
        }
    }

    if (roomAvailable) {
        int bookingId = bookings.size() + 1;
        int customerId = customers.size() + 1;
        customers.push_back(Customer(customerId, customerName, "Unknown"));
        bookings.push_back(Booking(bookingId, roomNumber, customerName, startDate, endDate));
        std::cout << "Booking confirmed!\n";
    } else {
        std::cout << "Sorry, the room is not available.\n";
    }
}

void addRoom(std::vector<Room>& rooms) {
    int roomNumber;
    std::string type;
    double price;

    // Room Number Validation
    while (true) {
        std::cout << "Enter room number: ";
        std::cin >> roomNumber;
        if (roomNumber <= 0) {
            std::cout << "Room number must be a positive integer. Try again.\n";
        } else if (!isRoomNumberValid(roomNumber, rooms)) {
            std::cout << "Room number " << roomNumber << " already exists. Try again.\n";
        } else {
            break;
        }
    }

    // Room Type Selection
    std::cout << "Select room type:\n";
    std::cout << "1. Single\n";
    std::cout << "2. Double\n";
    std::cout << "3. Suite\n";
    int typeChoice;
    while (true) {
        std::cin >> typeChoice;
        if (typeChoice == 1) {
            type = "Single";
            break;
        } else if (typeChoice == 2) {
            type = "Double";
            break;
        } else if (typeChoice == 3) {
            type = "Suite";
            break;
        } else {
            std::cout << "Invalid choice. Please select a valid room type (1, 2, or 3):\n";
        }
    }

    // Room Price Validation
    while (true) {
        std::cout << "Enter room price per night: Ksh";
        std::cin >> price;
        if (price <= 0) {
            std::cout << "Price must be a positive number. Try again.\n";
        } else {
            break;
        }
    }

    // Add room to the rooms vector
    rooms.push_back(Room(roomNumber, type, price, true));
    std::cout << "Room added successfully!\n";
}

int main() {
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
    std::vector<Customer> customers;

    rooms.push_back(Room(101, "Single", 100.0, true));
    rooms.push_back(Room(102, "Double", 150.0, true));

    int choice;
    while (true) {
        std::cout << "1. Add Room\n2. Make Booking\n3. View Available Rooms\n4. Exit\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addRoom(rooms);  // Add Room functionality with prompts and validation
                break;

            case 2:
                makeBooking(rooms, bookings, customers);
                break;

            case 3:
                displayAvailableRooms(rooms);
                break;

            case 4:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
