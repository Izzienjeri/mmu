#include "customer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Constructor
Customer::Customer(int id, const std::string& name, const std::string& contact, const std::string& password)
    : id(id), name(name), contactInfo(contact), password(password) {}

// Display details
void Customer::displayDetails() const {
    std::cout << "Customer ID: " << id << "\nName: " << name << "\nContact: " << contactInfo << "\n";
}

// Save customers to file
void Customer::saveCustomersToFile(const std::vector<Customer>& customers, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& customer : customers) {
        outFile << customer.id << "," << customer.name << "," << customer.contactInfo << "," << customer.password << "\n";
    }

    outFile.close();
}

// Load customers from file
std::vector<Customer> Customer::loadCustomersFromFile(const std::string& filename) {
    std::vector<Customer> customers;
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        return customers;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string idStr, name, contactInfo, password;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, contactInfo, ',');
        std::getline(ss, password, ',');
        int id = std::stoi(idStr);
        customers.push_back(Customer(id, name, contactInfo, password));
    }

    inFile.close();
    return customers;
}
