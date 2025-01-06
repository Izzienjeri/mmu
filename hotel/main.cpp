#include <iostream>
#include <vector>
#include "room.h"
#include "booking.h"
#include "customer.h"
#include "utils.h"

void displayAvailableRooms(const std::vector<Room>& rooms) {
    std::cout << "Available Rooms:\n";
    bool foundAvailable = false;
    for (const auto& room : rooms) {
        if (room.isAvailable) {
            room.displayDetails();
            foundAvailable = true;
        }
    }
    if (!foundAvailable) {
        std::cout << "No rooms are available at the moment.\n";
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

    // Show available rooms
    displayAvailableRooms(rooms);

    std::cout << "\n";

    // Room selection with validation
    std::cout << "Enter the room number you want to book: ";
    std::cin >> roomNumber;

    bool roomAvailable = false;
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && room.isAvailable) {
            roomAvailable = true;
            room.isAvailable = false; // Mark room as booked
            break;
        }
    }

    if (!roomAvailable) {
        std::cout << "Sorry, the room is not available. Please select another room.\n";
        return;
    }

    // Customer details input
    std::cout << "Enter customer name: ";
    std::cin >> customerName;

    // Date validation (Start Date)
    while (true) {
        std::cout << "Enter start date (YYYY-MM-DD): ";
        std::cin >> startDate;

        if (!isDateValid(startDate)) {
            std::cout << "Invalid date format! Please use YYYY-MM-DD format. Try again: ";
        } else if (isDateInPast(startDate)) {
            std::cout << "The start date cannot be in the past. Please enter a valid start date.\n";
        } else {
            break; // Exit loop if date is valid
        }
    }

    // Date validation (End Date)
    while (true) {
        std::cout << "Enter end date (YYYY-MM-DD): ";
        std::cin >> endDate;

        if (!isDateValid(endDate)) {
            std::cout << "Invalid date format! Please use YYYY-MM-DD format. Try again: ";
        } else if (isDateInPast(endDate)) {
            std::cout << "The end date cannot be in the past. Please enter a valid end date.\n";
        } else if (!isEndDateAfterStartDate(startDate, endDate)) {
            std::cout << "End date must be after the start date. Please enter valid dates.\n";
        } else {
            break; // Exit loop if date is valid
        }
    }

    // Add customer and booking
    int bookingId = bookings.size() + 1;
    int customerId = customers.size() + 1;
    customers.push_back(Customer(customerId, customerName, "Unknown"));
    bookings.push_back(Booking(bookingId, roomNumber, customerName, startDate, endDate));
    std::cout << "Booking confirmed!\n";
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
        std::cout << "Enter room price per night (positive value): Ksh ";
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

    // Adding predefined rooms
    rooms.push_back(Room(101, "Single", 100.0, true));
    rooms.push_back(Room(102, "Double", 150.0, true));
    rooms.push_back(Room(103, "Suite", 200.0, true));
    rooms.push_back(Room(104, "Single", 120.0, true));
    rooms.push_back(Room(105, "Double", 180.0, true));
    rooms.push_back(Room(106, "Suite", 250.0, true));

    int choice;
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Room\n2. Make Booking\n3. View Available Rooms\n4. Exit\n";
        std::cout << "\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addRoom(rooms);  // Add Room functionality with prompts and validation
                break;

            case 2:
                makeBooking(rooms, bookings, customers);
                break;

            case 3:
                std::cout << "\n";
                displayAvailableRooms(rooms);
                break;

            case 4:
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
