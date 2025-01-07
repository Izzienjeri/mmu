#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "room.h"
#include "booking.h"  // Include the header for Booking class
#include "customer.h" // Include the header for Customer class

// Function declarations for utility functions
void displayAvailableRooms(const std::vector<Room>& rooms);
bool isDateValid(const std::string& date);
bool isDateInPast(const std::string& date);
bool isEndDateAfterStartDate(const std::string& startDate, const std::string& endDate);
std::string toLower(const std::string& str);
bool isRoomNumberValid(int roomNumber, const std::vector<Room>& rooms);

void showAdminMenu();
void showUserMenu();
bool login(bool isAdminLogin, const std::vector<Customer>& customers);
void signup(std::vector<Customer>& customers); 
void addRoom(std::vector<Room>& rooms);
void markRoomAvailable(std::vector<Room>& rooms);

// Updated makeBooking function declaration with an additional parameter for user ID
void makeBooking(std::vector<Room>& rooms, std::vector<Booking>& bookings, std::vector<Customer>& customers, const std::string& userId);

#endif
