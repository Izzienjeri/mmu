#include "utils.h"
#include <iostream>
#include <cctype>
#include <ctime>
#include <unordered_map>
#include <fstream> 
#include <sstream> 
#include <vector>
#include <limits>





void displayAvailableRooms(const std::vector<Room>& rooms) {
    std::cout << "\n"; 
    std::cout << "**** Available Rooms ****\n";
    for (const auto& room : rooms) {
        if (room.isAvailable) {
            std::cout << "Room Number: " << room.roomNumber 
                      << ", Type: " << room.type 
                      << ", Price: Ksh " << room.pricePerNight 
                      << " 💰\n";
        }
    }
}

bool isDateValid(const std::string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    for (int i = 0; i < 10; ++i) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return false;
        }
    }
    return true;
}

bool isDateInPast(const std::string& date) {
    struct tm tm = {0};
    strptime(date.c_str(), "%Y-%m-%d", &tm);
    time_t inputDate = mktime(&tm);
    time_t now = time(0);
    return inputDate < now;
}

bool isEndDateAfterStartDate(const std::string& startDate, const std::string& endDate) {
    struct tm tmStart = {0}, tmEnd = {0};
    strptime(startDate.c_str(), "%Y-%m-%d", &tmStart);
    strptime(endDate.c_str(), "%Y-%m-%d", &tmEnd);
    
    time_t start = mktime(&tmStart);
    time_t end = mktime(&tmEnd);
    
    return difftime(end, start) > 0;
}

std::string toLower(const std::string& str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

bool isRoomNumberValid(int roomNumber, const std::vector<Room>& rooms) {
    for (const auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            return false; 
        }
    }
    return true; 
}

void showAdminMenu() {
    std::cout << "\nAdmin Menu 🛠️:\n";
    std::cout << "1. Add Room 🛏️\n";
    std::cout << "2. Mark Room Available ✔️\n";
    std::cout << "3. View Available Rooms 👀\n";
    std::cout << "4. Exit 🚪\n";
}

void showUserMenu() {
    std::cout << "\nUser Menu 👤:\n";
    std::cout << "1. Make Booking 📅\n";
    std::cout << "2. View Available Rooms 👀\n";
    std::cout << "3. Exit 🚪\n";
}

bool login(bool isAdminLogin, const std::vector<Customer>& customers) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    
    if (isAdminLogin) {
        
        if (username == "admin" && password == "pass") {
            std::cout << "Admin login successful. Welcome, Admin!\n";
            return true;
        } else {
            std::cout << "Invalid admin credentials. Please try again.\n";
            return false;
        }
    } else {
        
        for (const auto& customer : customers) {
            
            if (toLower(customer.name) == toLower(username) && customer.password == password) {
                std::cout << "User login successful. Welcome, " << username << "!\n";
                return true;
            }
        }
        std::cout << "Invalid username or password. Please try again.\n";
        return false;
    }
}



void signup(std::vector<Customer>& customers) {
    std::string name, contact, password;
    static int idCounter = customers.size() + 1;  

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout << "Enter your username: ";
    std::getline(std::cin, name);

    std::cout << "Enter your contact info: ";
    std::getline(std::cin, contact);

    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    
    customers.push_back(Customer(idCounter++, name, contact, password));

    
    Customer::saveCustomersToFile(customers, "customers.csv");

    std::cout << "Welcome, " << name << "! You have been registered successfully.\n";
}




void addRoom(std::vector<Room>& rooms) {
    int roomNumber;
    std::string type;
    double price;
    while (true) {
        std::cout << "Enter room number: ";
        std::cin >> roomNumber;
        if (roomNumber <= 0) {
            std::cout << "Room number must be a positive integer. Try again 💡.\n";
        } else if (!isRoomNumberValid(roomNumber, rooms)) {
            std::cout << "Room number " << roomNumber << " already exists. Try again 💡.\n";
        } else {
            break;
        }
    }

    std::cout << "Select room type 🛏️:\n";
    std::cout << "1. Single 🛏️\n";
    std::cout << "2. Double 🛏️🛏️\n";
    std::cout << "3. Suite 🏨\n";
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
            std::cout << "Invalid choice. Please select a valid room type (1, 2, or 3) 🛏️:\n";
        }
    }

    while (true) {
        std::cout << "Enter room price per night (positive value): Ksh ";
        std::cin >> price;
        if (price <= 0) {
            std::cout << "Price must be a positive number 💰. Try again.\n";
        } else {
            break;
        }
    }

    rooms.push_back(Room(roomNumber, type, price, true));
    std::cout << "Room added successfully! 🎉\n";
}

void markRoomAvailable(std::vector<Room>& rooms, std::vector<Booking>& bookings) {
    std::cout << "\n**** Unavailable Rooms ****\n";
    
    
    bool foundUnavailable = false;
    for (const auto& room : rooms) {
        if (!room.isAvailable) {
            std::cout << "Room Number: " << room.roomNumber 
                      << ", Type: " << room.type 
                      << ", Price: Ksh " << room.pricePerNight 
                      << " 💰 (Unavailable)\n";
            foundUnavailable = true;
        }
    }

    if (!foundUnavailable) {
        std::cout << "All rooms are available! 🎉\n";
        return;
    }

    int roomNumber;
    std::cout << "Enter the room number you want to mark as available: ";
    std::cin >> roomNumber;

    bool roomFound = false;
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && !room.isAvailable) {
            room.isAvailable = true; 
            std::cout << "Room " << roomNumber << " is now available ✔️.\n";
            
            
            for (auto it = bookings.begin(); it != bookings.end(); ) {
                if (it->roomNumber == roomNumber) {
                    std::cout << "Booking for room " << roomNumber << " has been canceled.\n";
                    it = bookings.erase(it); 
                } else {
                    ++it;
                }
            }
            
            
            std::ofstream bookingsFile("bookings.csv");
            if (bookingsFile.is_open()) {
                for (const auto& booking : bookings) {
                    bookingsFile << booking.customerName << ","
                                 << booking.bookingId << ","
                                 << booking.roomNumber << ","
                                 << booking.startDate << ","
                                 << booking.endDate << "\n";
                }
                bookingsFile.close();
            } else {
                std::cout << "Error opening bookings.csv file.\n";
            }

            roomFound = true;
            break;
        }
    }

    if (!roomFound) {
        std::cout << "Room number not found or already available ❌.\n";
    }

    
    std::ofstream roomsFile("rooms.csv");
    if (roomsFile.is_open()) {
        for (const auto& room : rooms) {
            roomsFile << room.roomNumber << ","
                      << room.type << ","
                      << room.pricePerNight << ","
                      << (room.isAvailable ? 1 : 0) << "\n";
        }
        roomsFile.close();
    } else {
        std::cout << "Error opening rooms.csv file.\n";
    }
}


void printBookingConfirmation(int bookingId, const std::string& customerName, int roomNumber, 
                               const std::string& roomType, const std::string& startDate, 
                               const std::string& endDate, double totalPrice) {
    std::cout << "\n==================== Booking Confirmation 🏨 ====================\n";
    std::cout << "Booking ID: " << bookingId << "\n";
    std::cout << "Customer Name: " << customerName << "\n";
    std::cout << "Room Number: " << roomNumber << "\n";
    std::cout << "Room Type: " << roomType << "\n";
    std::cout << "Check-in Date: " << startDate << "\n";
    std::cout << "Check-out Date: " << endDate << "\n";
    std::cout << "Total Price: Ksh " << totalPrice << " 💸\n";
    std::cout << "==================== Thank you for booking with us! 🙏 ====================\n\n";
}

void makeBooking(std::vector<Room>& rooms, std::vector<Booking>& bookings, std::vector<Customer>& customers, const std::string& userName) {
    int roomNumber;
    std::string startDate, endDate;

    
    displayAvailableRooms(rooms);
    std::cout << "\n";

    
    std::cout << "Enter the room number you want to book: ";
    std::cin >> roomNumber;
    
    bool roomAvailable = false;
    double roomPrice = 0.0;
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && room.isAvailable) {
            roomAvailable = true;
            roomPrice = room.pricePerNight; 
            room.isAvailable = false; 
            break;
        }
    }

    if (!roomAvailable) {
        std::cout << "Sorry, the room is not available. Please select another room.\n";
        return;
    }

    
    std::string customerName = userName;

    
    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::cin >> startDate;
    
    while (!isDateValid(startDate) || isDateInPast(startDate)) {
        if (!isDateValid(startDate)) {
            std::cout << "Invalid date format! Please use YYYY-MM-DD format. Try again: ";
        } else {
            std::cout << "Start date cannot be in the past or today. Please enter a valid start date: ";
        }
        std::cin >> startDate;
    }

    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::cin >> endDate;

    while (!isDateValid(endDate) || !isEndDateAfterStartDate(startDate, endDate)) {
        if (!isDateValid(endDate)) {
            std::cout << "Invalid date format! Please use YYYY-MM-DD format. Try again: ";
        } else {
            std::cout << "End date must be after start date. Please enter a valid end date: ";
        }
        std::cin >> endDate;
    }

    
    struct tm tmStart = {0}, tmEnd = {0};
    strptime(startDate.c_str(), "%Y-%m-%d", &tmStart);
    strptime(endDate.c_str(), "%Y-%m-%d", &tmEnd);
    
    time_t start = mktime(&tmStart);
    time_t end = mktime(&tmEnd);
    double totalPrice = difftime(end, start) / (60 * 60 * 24) * roomPrice;

    
    int bookingId = bookings.size() + 1;

    
    bookings.push_back(Booking(bookingId, roomNumber, customerName, startDate, endDate));

    
    printBookingConfirmation(bookingId, customerName, roomNumber, 
                              (roomPrice == 100.0 ? "Single" : (roomPrice == 150.0 ? "Double" : "Suite")),
                              startDate, endDate, totalPrice);

    
    std::ofstream bookingsFile("bookings.csv", std::ios::app);
    if (bookingsFile.is_open()) {
        bookingsFile << customerName << "," << bookingId << "," << roomNumber << "," << startDate << "," << endDate << "\n";
        bookingsFile.close();
    } else {
        std::cout << "Error opening bookings.csv file.\n";
    }

    
    std::ofstream roomsFile("rooms.csv");
    if (roomsFile.is_open()) {
        for (const auto& room : rooms) {
            roomsFile << room.roomNumber << "," << room.type << "," << room.pricePerNight 
                      << "," << (room.isAvailable ? 1 : 0) << "\n";
        }
        roomsFile.close();
    } else {
        std::cout << "Error opening rooms.csv file.\n";
    }
}
