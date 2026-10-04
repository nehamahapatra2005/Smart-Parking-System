# Smart Parking System

A desktop-based parking management application built using C++ and Qt 6. The project is designed to handle common parking operations such as registering vehicles, assigning parking slots, searching for vehicles, calculating parking fees, and completing checkout through a simple graphical interface.

## About the Project

Managing parking manually can become difficult when there are multiple vehicles and parking slots to keep track of. This project was developed as a simple software solution to make these tasks easier and more organized.

The application uses C++ for the core parking logic and Qt 6 for the graphical user interface. Different classes are used to handle vehicles, parking slots, parking operations, tickets, and billing.

The project also uses text files to store important parking information, allowing the data to be restored when the application is opened again.

## Features

- Register vehicles with vehicle number, type, and owner name
- Automatically assign available parking slots
- View available and occupied parking slots
- Search for registered vehicles
- View current parking information
- Calculate parking fees based on parking duration
- Generate parking billing information
- Complete vehicle checkout
- Automatically release a parking slot after checkout
- Dashboard showing parking statistics
- Light and dark mode
- Save and restore parking data using text files

## Technologies Used

- C++17
- Qt 6
- Qt Widgets
- C++ STL
- File Handling
- qmake
- g++
- Zorin OS / Linux

## How It Works

The application is divided into two main parts.

### Graphical Interface

The Qt-based interface allows the user to interact with the system through dashboards, buttons, forms, parking slot cards, and billing screens.

### Application Logic

The C++ classes handle the actual parking operations, including vehicle registration, slot assignment, searching, billing, and checkout.

The basic workflow is:

Register Vehicle
       ↓
Find Available Slot
       ↓
Park Vehicle
       ↓
View / Search Vehicle
       ↓
Calculate Parking Fee
       ↓
Complete Checkout
       ↓
Release Parking Slot

## Project Structure

Smart-Parking-System/
│
├── data/
│   ├── parking_slots.txt
│   └── vehicles.txt
│
├── docs/
│
├── gui/
│   ├── main.cpp
│   ├── MainWindow.cpp
│   ├── MainWindow.h
│   ├── ThemeToggle.cpp
│   ├── ThemeToggle.h
│   └── SmartParking.pro
│
├── include/
│   ├── Billing.h
│   ├── ParkingLot.h
│   ├── ParkingSlot.h
│   ├── Ticket.h
│   └── Vehicle.h
│
├── src/
│   ├── Billing.cpp
│   ├── main.cpp
│   ├── ParkingLot.cpp
│   ├── ParkingSlot.cpp
│   ├── Ticket.cpp
│   └── Vehicle.cpp
│
├── tests/
│
├── .gitignore
└── README.md

## Main Classes

### Vehicle

Stores information about a vehicle, including its vehicle number, type, and owner's name.

### ParkingSlot

Represents an individual parking slot and keeps track of whether it is available or occupied.

### ParkingLot

Manages the parking slots and handles parking, slot assignment, vehicle removal, and vehicle searching.

### Ticket

Stores parking-related information such as ticket number, vehicle, slot number, and parking fee.

### Billing

Handles parking fee calculation and billing information.

### MainWindow

Controls the Qt graphical interface and connects user actions with the parking system.

## Parking and Slot Management

When a vehicle is registered and parked, the system checks the available parking slots and assigns one to the vehicle.

The dashboard shows the current parking status, including total slots, available slots, and occupied slots.

When a vehicle completes checkout, its assigned slot is released and becomes available again.

## Billing

The billing section allows the user to select a currently parked vehicle and enter the parking duration.

The current parking rate is:

₹20 per hour

For example:

Parking Duration : 3 hours
Rate             : ₹20/hour
Total Fee        : ₹60

After checkout is completed, the vehicle is removed from the parking slot and the slot becomes available again.

## Data Persistence

The project uses simple text files to store parking information.

### vehicles.txt

Stores registered vehicle information and the current parking slot.

Format:

vehicleNumber|vehicleType|ownerName|slot

A slot value of -1 means that the vehicle is registered but is currently not parked.

### parking_slots.txt

Stores the current parking slot assignments.

Format:

slotNumber|vehicleNumber

When the application starts, this information is loaded again so that the previous parking state can be restored.

## Object-Oriented Programming

The project uses C++ OOP concepts to keep the code organized and modular.

Concepts used include:

- Classes and Objects
- Encapsulation
- Constructors
- Member Functions
- Access Specifiers
- Pointers
- STL Containers
- Association between classes

## User Interface

The application contains separate sections for different tasks:

- Dashboard - Overview of the parking area
- Parking Slots - View current slot status
- Vehicles - View vehicle information
- Billing - Calculate fees and complete checkout
- Settings - Application preferences and theme selection

The application also supports both light mode and dark mode.

## Running the Project on Linux

The project was developed and tested on Zorin OS Linux.

### Requirements

- Qt 6
- qmake6
- g++
- make

### Build the Project

Open a terminal and navigate to the GUI directory:

cd ~/Desktop/Smart-Parking-System/gui

Generate the build files:

qmake6 SmartParking.pro

Compile the project:

make -j$(nproc)

Run the application:

./SmartParking

After the project has already been built, you can normally start it again using:

./SmartParking

## Screenshots

Screenshots of the application can be added here to show the dashboard, parking slots, vehicle management, billing, and light/dark mode.

## Limitations

The current version focuses on software-based parking management.

It does not include physical hardware features such as:

- RFID readers
- Parking sensors
- Automatic Number Plate Recognition (ANPR)
- Automatic parking barriers
- Hardware-based slot detection

These features are outside the current scope of the project.

## Future Improvements

Possible future improvements include:

- Database integration
- User authentication
- Parking history and reports
- Online payment support
- RFID-based vehicle identification
- Automatic Number Plate Recognition
- Real-time parking sensors
- Hardware integration for automated parking management

## What This Project Demonstrates

This project provides practical experience with:

- C++ programming
- Object-Oriented Programming
- STL containers
- File handling
- Qt GUI development
- Event-driven programming
- Software architecture
- Linux-based application development

## Author

Neha Mahapatra

BTech - Computer Science
ITER, SOA University
