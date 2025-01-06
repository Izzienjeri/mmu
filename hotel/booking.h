#ifndef BOOKING_H
#define BOOKING_H

#include <string>

class Booking {
public:
    int bookingId;
    int roomNumber;
    std::string customerName;
    std::string startDate;
    std::string endDate;

    Booking(int id, int room, const std::string& customer, const std::string& start, const std::string& end);
    void displayDetails() const ;
};

#endif