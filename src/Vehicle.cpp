#include "../include/Vehicle.h"
#include <iostream>
#include <utility>  // for std::move

// Stores the details passed while creating a vehicle
Vehicle::Vehicle(std::string number, std::string type, std::string owner)
    : vehicleNumber(std::move(number)),
      vehicleType(std::move(type)),
      ownerName(std::move(owner)) {
}

// Prints the vehicle details
void Vehicle::displayVehicle() const {
    std::cout << "\n===== Vehicle Details =====\n";
    std::cout << "Vehicle Number : " << vehicleNumber << '\n';
    std::cout << "Vehicle Type   : " << vehicleType << '\n';
    std::cout << "Owner Name     : " << ownerName << '\n';
    std::cout << "===========================\n";
}