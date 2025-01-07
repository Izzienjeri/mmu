// customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>

class Customer {
public:
    int id;
    std::string name;
    std::string contactInfo;
    std::string password;  // New field for storing password

    Customer(int id, const std::string& name, const std::string& contact, const std::string& password);

    void displayDetails() const;

    static void saveCustomersToFile(const std::vector<Customer>& customers, const std::string& filename);
    static std::vector<Customer> loadCustomersFromFile(const std::string& filename);
};

#endif // CUSTOMER_H
