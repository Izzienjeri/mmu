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
                {
                    int number;
                    std::string type;
                    double price;
                    std::cout << "Enter room number, type, and price: ";
                    std::cin >> number >> type >> price;
                    rooms.push_back(Room(number, type, price, true));
                    std::cout << "Room added successfully!\n";
                }
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
