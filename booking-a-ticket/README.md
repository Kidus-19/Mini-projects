
# Plane Ticket Booking System - README

## Overview
This is a simple console-based Plane Ticket Booking System written in C++. It allows users to book tickets for flights, providing options for one-way or round trips and selecting between economy and business classes.

## Features
- **User Input:** Collects passenger names, trip type, travel dates, and class preferences.
- **Ticket Generation:** Generates unique ticket IDs using random characters and numbers.
- **Validation:** Ensures user inputs are valid (e.g., dates, ticket counts).

## Requirements
- C++ compiler (C++11 or later recommended)

## How to Compile and Run
1. **Compile the code:**
   ```bash
   g++ -o TicketBooking TicketBooking.cpp
   ```

2. **Run the executable:**
   ```bash
   ./TicketBooking
   ```

## Usage
1. Follow on-screen prompts to book tickets.
2. Enter the number of tickets (up to 5).
3. Provide passenger names and select trip options.
4. Review ticket details displayed at the end of the booking process.

## Notes
- Ensure your terminal supports clearing the screen (`system("cls")`).
- The program uses random functions for ticket ID generation.

## Author
- Kidus Yohannes
