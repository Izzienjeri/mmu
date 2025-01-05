#include "booking.h"
#include <iostream>

Booking::Booking(int id, int room, const std::string& customer, const std::string& start, const std::string& end)
    : bookingId(id), roomNumber(room), customerName(customer), startDate(start), endDate(end) {}

void Booking::displayDetails() const {
    std::cout << "Booking ID: " << bookingId
              << "\nRoom: " << roomNumber
              << "\nCustomer: " << customerName
              << "\nFrom: " << startDate << " to " << endDate << "\n";
}
