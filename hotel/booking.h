#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>

class Booking {
public:
    int bookingId;
    int roomNumber;
    std::string customerName;
    std::string startDate;
    std::string endDate;

    Booking(int id, int room, const std::string& customer, const std::string& start, const std::string& end);
    void displayDetails() const;
    
    static std::vector<Booking> loadBookingsFromCSV(const std::string& filename);
    static void saveBookingsToCSV(const std::string& filename, const std::vector<Booking>& bookings);
};

#endif
