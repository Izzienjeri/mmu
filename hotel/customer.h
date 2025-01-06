#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
public:
    int id;
    std::string name;
    std::string contactInfo;

    Customer(int id, const std::string& name, const std::string& contact);
    void displayDetails() const;
};

#endif