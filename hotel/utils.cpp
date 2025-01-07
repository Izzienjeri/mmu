#include "utils.h"
#include <iostream>
#include <cctype>
#include <ctime>
#include <unordered_map>

// 🛏️ Utility function definitions

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
            return false; // Room number already exists 🚫
        }
    }
    return true; // Room number is valid ✅
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

bool login(bool isAdminLogin) {
    std::unordered_map<std::string, std::pair<std::string, bool>> userDatabase = {
        {"user1", {"pass1", false}},  // Normal user
        {"user2", {"pass2", false}},  // Normal user
        {"admin", {"adminpass", true}}  // Admin user
    };
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (userDatabase.find(username) == userDatabase.end()) {
        std::cout << "No such account found. Please sign up first (if a normal user) 📝.\n";
        return false;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    if (isAdminLogin) {
        if (userDatabase[username].second && userDatabase[username].first == password) {
            std::cout << "Login successful as Admin 👑.\n";
            return true;
        } else {
            std::cout << "Incorrect admin credentials ❌.\n";
            return false;
        }
    } else {
        if (!userDatabase[username].second && userDatabase[username].first == password) {
            std::cout << "Login successful 👌.\n";
            return true;
        } else {
            std::cout << "Incorrect username or password ❌.\n";
            return false;
        }
    }
}

void signup() {
    std::unordered_map<std::string, std::pair<std::string, bool>> userDatabase;
    std::string username, password;
    std::cout << "Enter new username: ";
    std::cin >> username;

    if (userDatabase.find(username) != userDatabase.end()) {
        std::cout << "Username already exists. Please choose another one 🚫.\n";
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    userDatabase[username] = {password, false};
    std::cout << "User account created successfully ✅.\n";
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

void markRoomAvailable(std::vector<Room>& rooms) {
    int roomNumber;
    std::cout << "Enter room number to mark as available: ";
    std::cin >> roomNumber;

    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber) {
            room.isAvailable = true;
            std::cout << "Room " << roomNumber << " is now available ✔️.\n";
            return;
        }
    }

    std::cout << "Room number not found ❌.\n";
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
    double roomPrice = 0.0;
    for (auto& room : rooms) {
        if (room.roomNumber == roomNumber && room.isAvailable) {
            roomAvailable = true;
            roomPrice = room.pricePerNight; // Store price of selected room 💸
            room.isAvailable = false; // Mark room as booked ✅
            break;
        }
    }

    if (!roomAvailable) {
        std::cout << "Sorry, the room is not available. Please select another room 💡.\n";
        return;
    }

    // Customer details input
    std::cout << "Enter customer name: ";
    std::cin >> customerName;

    // Date validation
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

    // Calculate total price
    struct tm tmStart = {0}, tmEnd = {0};
    strptime(startDate.c_str(), "%Y-%m-%d", &tmStart);
    strptime(endDate.c_str(), "%Y-%m-%d", &tmEnd);
    
    time_t start = mktime(&tmStart);
    time_t end = mktime(&tmEnd);
    double totalPrice = difftime(end, start) / (60 * 60 * 24) * roomPrice;

    // Add customer and booking
    int bookingId = bookings.size() + 1;
    int customerId = customers.size() + 1;
    customers.push_back(Customer(customerId, customerName, "Unknown"));
    bookings.push_back(Booking(bookingId, roomNumber, customerName, startDate, endDate));

    // Print booking confirmation and receipt
    std::cout << "\n==================== Booking Confirmation 🏨 ====================\n";
    std::cout << "Booking ID: " << bookingId << "\n";
    std::cout << "Customer Name: " << customerName << "\n";
    std::cout << "Room Number: " << roomNumber << "\n";
    std::cout << "Room Type: " << (roomPrice == 100.0 ? "Single 🛏️" : (roomPrice == 150.0 ? "Double 🛏️🛏️" : "Suite 🏨")) << "\n";
    std::cout << "Check-in Date: " << startDate << "\n";
    std::cout << "Check-out Date: " << endDate << "\n";
    std::cout << "Total Price: Ksh " << totalPrice << " 💸\n";
    std::cout << "==================== Thank you for booking with us! 🙏 ====================\n\n";
}
