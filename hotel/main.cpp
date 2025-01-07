#include <iostream>
#include <vector>
#include <unordered_map>
#include "room.h"
#include "booking.h"
#include "customer.h"
#include "utils.h"


int main() {
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
    std::vector<Customer> customers;

    // Predefined rooms
    rooms.push_back(Room(101, "Single", 100.0, true));
    rooms.push_back(Room(102, "Double", 150.0, true));
    rooms.push_back(Room(103, "Suite", 200.0, true));
    rooms.push_back(Room(104, "Single", 120.0, true));
    rooms.push_back(Room(105, "Double", 180.0, true));
    rooms.push_back(Room(106, "Suite", 250.0, true));

    int actionChoice;
    bool loggedIn = false;
    bool isAdmin = false;

    while (true) {
        std::cout << "\nWelcome to Hotel Booking System\n";
        std::cout << "1. Login\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Sign Up (Normal Users Only)\n";
        std::cout << "4. Exit\n";
        std::cout << "\n"; 
        std::cout << "Enter your choice: ";
        std::cin >> actionChoice;

        switch (actionChoice) {
            case 1: {  // Login as User
                loggedIn = login(false); // Pass false for normal user login
                if (loggedIn && !isAdmin) {
                }
                break;
            }

           case 2: {
              // Login as Admin
            loggedIn = login(true); // Pass true for admin login
                if (loggedIn) {
                    isAdmin = true;
                    while (isAdmin) {
                        showAdminMenu();
                        std::cout << "Enter your choice: ";
                        std::cin >> actionChoice;

                        switch (actionChoice) {
                            case 1:  // Add Room
                                addRoom(rooms);
                                break;
                            case 2:  // Mark Room Available
                                markRoomAvailable(rooms);
                                break;
                            case 3:  // View Available Rooms
                                displayAvailableRooms(rooms);
                                break;
                            case 4:  // Exit Admin Menu
                                std::cout << "Logging out as Admin...\n";
                                isAdmin = false;
                                loggedIn = false;
                                break;
                            default:
                                std::cout << "Invalid choice. Please try again.\n";
                                break;
                        }
                    }
                }
            break;
        }


            case 3: {  // Sign Up
                signup();
                break;
            }

            case 4: {  // Exit
                std::cout << "Exiting...\n";
                return 0;
            }

            default: {
                std::cout << "Invalid choice. Please try again.\n";
                continue;
            }
        }

        if (!loggedIn) {
            std::cout << "You need to log in first.\n";
            continue;
        }

        if (loggedIn && !isAdmin) {
            while (true) {  // Stay in user menu
                showUserMenu();
                std::cout << "Enter your choice: ";
                std::cin >> actionChoice;

                switch (actionChoice) {
                    case 1: {  // Make Booking
                        makeBooking(rooms, bookings, customers); 
                        break;
                    }

                    case 2: {  // View Available Rooms
                        displayAvailableRooms(rooms);
                        break;
                    }

                    case 3: {  // Exit
                        std::cout << "Returning to the main menu...\n";
                        loggedIn = false;
                        break;
                    }

                    default: {
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                    }
                }

                if (!loggedIn) break;  // Exit user menu
            }
        }
    }

    return 0;
}