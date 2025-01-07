#include <iostream>
#include <vector>
#include <unordered_map>
#include "room.h"
#include "booking.h"
#include "customer.h"
#include "utils.h"


const std::string ADMIN_PASSWORD = "Njeri";


std::unordered_map<std::string, bool> userDatabase;  


bool login() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (userDatabase.find(username) == userDatabase.end()) {
        std::cout << "No such account found. Please sign up first.\n";
        return false;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    
    if (password == ADMIN_PASSWORD && userDatabase[username]) {
        std::cout << "Login successful as Admin.\n";
        return true;  
    } else if (password != ADMIN_PASSWORD && !userDatabase[username]) {
        std::cout << "Login successful as User.\n";
        return false;  
    } else {
        std::cout << "Incorrect password.\n";
        return false;  
    }
}


void signup() {
    std::string username, password;
    std::cout << "Enter new username: ";
    std::cin >> username;

    
    if (userDatabase.find(username) != userDatabase.end()) {
        std::cout << "Username already exists. Please choose another one.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    if (password == ADMIN_PASSWORD) {
        userDatabase[username] = true;  
        std::cout << "Admin account created successfully.\n";
    } else {
        userDatabase[username] = false;  
        std::cout << "User account created successfully.\n";
    }
}


void showAdminMenu() {
    std::cout << "\nAdmin Menu:\n";
    std::cout << "1. Add Room\n";
    std::cout << "2. Mark Room Available\n";
    std::cout << "3. View Available Rooms\n";
    std::cout << "4. Exit\n";
}


void showUserMenu() {
    std::cout << "\nUser Menu:\n";
    std::cout << "1. Make Booking\n";
    std::cout << "2. View Available Rooms\n";
    std::cout << "3. Exit\n";
}


void addRoom(std::vector<Room>& rooms) {
    int roomNumber;
    std::string type;
    double price;

    
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

    
    while (true) {
        std::cout << "Enter room price per night (positive value): Ksh ";
        std::cin >> price;
        if (price <= 0) {
            std::cout << "Price must be a positive number. Try again.\n";
        } else {
            break;
        }
    }

    
    rooms.push_back(Room(roomNumber, type, price, true));
    std::cout << "Room added successfully!\n";
}


void markRoomAvailable(std::vector<Room>& rooms) {
    int roomNumber;
    std::cout << "Enter room number to mark as available: ";
    std::cin >> roomNumber;

    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            room.isAvailable = true;
            std::cout << "Room " << roomNumber << " is now available.\n";
            return;
        }
    }

    std::cout << "Room number not found.\n";
}

int main() {
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
    std::vector<Customer> customers;

    
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
        std::cout << "3. Sign Up\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> actionChoice;

        switch (actionChoice) {
            case 1: 
                loggedIn = login();
                if (loggedIn) {
                    isAdmin = false;  
                    std::cout << "You are logged in as a user.\n";
                }
                break;

            case 2: 
                loggedIn = login();
                if (loggedIn) {
                    isAdmin = true;  
                    std::cout << "You are logged in as an admin.\n";
                }
                break;

            case 3: 
                signup();
                break;

            case 4: 
                std::cout << "Exiting...\n";
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                continue;
        }

        
        if (!loggedIn) {
            std::cout << "You need to log in first.\n";
            continue;  
        }

        if (loggedIn && !isAdmin) {
            
            showUserMenu();
            std::cout << "Enter your choice: ";
            std::cin >> actionChoice;

            switch (actionChoice) {
                case 1:
                    
                    break;

                case 2:
                    
                    displayAvailableRooms(rooms);
                    break;

                case 3:
                    std::cout << "Exiting...\n";
                    return 0;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    continue;
            }
        } else if (loggedIn && isAdmin) {
            
            showAdminMenu();
            std::cout << "Enter your choice: ";
            std::cin >> actionChoice;

            switch (actionChoice) {
                case 1:
                    addRoom(rooms);
                    break;

                case 2:
                    markRoomAvailable(rooms);
                    break;

                case 3:
                    
                    displayAvailableRooms(rooms);
                    break;

                case 4:
                    std::cout << "Exiting...\n";
                    return 0;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    continue;
            }
        }
    }

    return 0;
}
