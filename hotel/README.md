# Izzie's Hotel Booking System

## Overview
This is a command-line hotel booking system designed for managing room reservations, customer sign-ups, and administrative tasks such as adding rooms and marking them as available. It provides a simple user interface for both regular users and administrators to manage bookings and view room availability.

The system supports logging in as both a regular customer and an admin, where the admin can manage room listings and bookings. Users can make bookings based on room availability.

## Features

- **Customer Sign-Up**: Customers can sign up with their username, contact information, and password.
- **Login as User/Admin**: Login functionality for customers and administrators.
- **Room Management (Admin)**: Admin can add rooms, view available rooms, and mark rooms as available/unavailable.
- **Booking Management (User)**: Customers can view available rooms and make bookings.
- **Booking Confirmation**: After booking a room, a confirmation with booking details is displayed.
- **Date Validation**: Ensures dates are valid and in the correct format.

## Installation

### Prerequisites

- C++11 or higher
- Compiler: `g++` or any other C++ compiler
- CSV Files for storing rooms, bookings, and customers:
  - `rooms.csv`: Stores available rooms.
  - `bookings.csv`: Stores room booking details.
  - `customers.csv`: Stores customer details.

### Setup

1. Clone the repository or download the source code files.
2. Compile the C++ files using a C++ compiler:
   ```bash
   g++ main.cpp utils.cpp -o hotel_booking_system
