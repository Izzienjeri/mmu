#include <iostream>
#include <vector>
#include "room.h"
#include "booking.h"
#include "customer.h"
#include "utils.h"

int main() {
    // Load data from CSV files
    std::vector<Room> rooms = loadRoomsFromCSV("rooms.csv");
    std::vector<Booking> bookings = Booking::loadBookingsFromCSV("bookings.csv");
    std::vector<Customer> customers = Customer::loadCustomersFromFile("customers.csv");

    bool loggedIn = false;
    bool isAdmin = false;
    std::string username;  // Declare username here so it can be accessed throughout the program

    while (true) {
        std::cout << "\nWelcome to the Hotel Booking System\n";
        std::cout << "1. Login as User\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Sign Up (Normal Users Only)\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int actionChoice;
        std::cin >> actionChoice;

        switch (actionChoice) {
            case 1: {  // Login as User
                loggedIn = false;  // Reset login state
                std::string password;

                std::cout << "Enter username: ";
                std::cin >> username;  // Set the logged-in username
                std::cout << "Enter password: ";
                std::cin >> password;

                for (const auto& customer : customers) {
                    if (customer.name == username && customer.password == password) {
                        loggedIn = true;
                        isAdmin = false;
                        std::cout << "Login successful. Welcome, " << username << "!\n";
                        break;
                    }
                }

                if (!loggedIn) {
                    std::cout << "Invalid username or password. Please try again.\n";
                }

                break;
            }

            case 2: {  // Login as Admin
                loggedIn = false;
                std::string password;

                std::cout << "Enter admin username: ";
                std::cin >> username;
                std::cout << "Enter admin password: ";
                std::cin >> password;

                if (username == "admin" && password == "pass") {
                    loggedIn = true;
                    isAdmin = true;
                    std::cout << "Admin login successful!\n";
                } else {
                    std::cout << "Invalid admin credentials. Please try again.\n";
                }
                break;
            }

            case 3: {  // Sign Up
                if (isAdmin) {
                    std::cout << "Admin cannot sign up. Please log in as admin.\n";
                    break;
                }

                signup(customers);
                loggedIn = true;
                isAdmin = false;
                break;
            }

            case 4: {  // Exit
                std::cout << "Exiting...\n";
                saveRoomsToCSV("rooms.csv", rooms);
                Booking::saveBookingsToCSV("bookings.csv", bookings);
                Customer::saveCustomersToFile(customers, "customers.csv");
                return 0;
            }

            default: {
                std::cout << "Invalid choice. Please try again.\n";
                continue;
            }
        }

        if (loggedIn) {
            if (isAdmin) {
                while (isAdmin) {
                    showAdminMenu();
                    std::cout << "Enter your choice: ";
                    std::cin >> actionChoice;

                    switch (actionChoice) {
                        case 1:  // Add Room
                            addRoom(rooms);
                            saveRoomsToCSV("rooms.csv", rooms);
                            break;

                        case 2:  // Mark Room Available
                            markRoomAvailable(rooms);
                            saveRoomsToCSV("rooms.csv", rooms);
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
            } else {  // User Menu
                while (loggedIn) {
                    showUserMenu();
                    std::cout << "Enter your choice: ";
                    std::cin >> actionChoice;

                    switch (actionChoice) {
                        case 1:  // Make Booking
                            makeBooking(rooms, bookings, customers, username); // Pass the logged-in user's name
                            break;

                        case 2:  // View Available Rooms
                            displayAvailableRooms(rooms);
                            break;

                        case 3:  // Logout
                            std::cout << "Logging out...\n";
                            loggedIn = false;
                            break;

                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
            }
        } else {
            std::cout << "You need to log in to access this menu.\n";
        }
    }

    // Save data to CSV files before exiting
    saveRoomsToCSV("rooms.csv", rooms);
    Booking::saveBookingsToCSV("bookings.csv", bookings);
    Customer::saveCustomersToFile(customers, "customers.csv");

    return 0;
}