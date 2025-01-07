#include <iostream>
#include <vector>
#include "room.h"
#include "booking.h"
#include "customer.h"
#include "utils.h"

int main() {
    
    std::vector<Room> rooms = loadRoomsFromCSV("rooms.csv");
    std::vector<Booking> bookings = Booking::loadBookingsFromCSV("bookings.csv");
    std::vector<Customer> customers = Customer::loadCustomersFromFile("customers.csv");

    bool loggedIn = false;
    bool isAdmin = false;
    std::string username;  

    while (true) {
        std::cout << "\nWelcome to Izzie's Hotel Booking System\n";
        std::cout << "1. Login as User\n";
        std::cout << "2. Login as Admin\n";
        std::cout << "3. Sign Up\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int actionChoice;
        std::cin >> actionChoice;

        switch (actionChoice) {
            case 1: {  
                loggedIn = false;  
                std::string password;

                std::cout << "Enter username: ";
                std::cin >> username;  
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

            case 2: {  
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

            case 3: {  
                if (isAdmin) {
                    std::cout << "Admin cannot sign up. Please log in as admin.\n";
                    break;
                }

                signup(customers);
                loggedIn = true;
                isAdmin = false;
                break;
            }

            case 4: {  
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
                        case 1:  
                            addRoom(rooms);
                            saveRoomsToCSV("rooms.csv", rooms);
                            break;

                        case 2:  
                            markRoomAvailable(rooms, bookings);
                            saveRoomsToCSV("rooms.csv", rooms);
                            break;

                        case 3:  
                            displayAvailableRooms(rooms);
                            break;

                        case 4:  
                            std::cout << "Logging out as Admin...\n";
                            isAdmin = false;
                            loggedIn = false;
                            break;

                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                            break;
                    }
                }
            } else {  
                while (loggedIn) {
                    showUserMenu();
                    std::cout << "Enter your choice: ";
                    std::cin >> actionChoice;

                    switch (actionChoice) {
                        case 1:  
                            makeBooking(rooms, bookings, customers, username); 
                            break;

                        case 2:  
                            displayAvailableRooms(rooms);
                            break;

                        case 3:  
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

    
    saveRoomsToCSV("rooms.csv", rooms);
    Booking::saveBookingsToCSV("bookings.csv", bookings);
    Customer::saveCustomersToFile(customers, "customers.csv");

    return 0;
}