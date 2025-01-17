#include "booking.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


Booking::Booking(int id, int room, const std::string& customer, const std::string& start, const std::string& end)
    : bookingId(id), roomNumber(room), customerName(customer), startDate(start), endDate(end) {}


void Booking::displayDetails() const {
    std::cout << "Booking ID: " << bookingId
              << "\nRoom: " << roomNumber
              << "\nCustomer: " << customerName
              << "\nFrom: " << startDate << " to " << endDate << "\n";
}


std::vector<Booking> Booking::loadBookingsFromCSV(const std::string& filename) {
    std::vector<Booking> bookings;
    std::ifstream file(filename);
    std::string line;
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int id, room;
        std::string customer, start, end;
        
        std::getline(ss, customer, ',');
        ss >> id;
        ss.ignore();  
        ss >> room;
        ss.ignore();  
        std::getline(ss, start, ',');
        std::getline(ss, end, ',');

        bookings.push_back(Booking(id, room, customer, start, end));
    }
    
    return bookings;
}


void Booking::saveBookingsToCSV(const std::string& filename, const std::vector<Booking>& bookings) {
    std::ofstream file(filename);
    
    for (const auto& booking : bookings) {
        file << booking.customerName << ","
             << booking.bookingId << ","
             << booking.roomNumber << ","
             << booking.startDate << ","
             << booking.endDate << "\n";
    }
}
