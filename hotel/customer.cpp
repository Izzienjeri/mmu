#include "customer.h"
#include <iostream>

Customer::Customer(int id, const std::string& name, const std::string& contact)
    : id(id), name(name), contactInfo(contact) {}

void Customer::displayDetails() const {
    std::cout << "Customer ID: " << id << "\nName: " << name << "\nContact: " << contactInfo << "\n";
}