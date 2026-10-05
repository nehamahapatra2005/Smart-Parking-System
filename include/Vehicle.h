#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

// stores basic info about a vehicle
class Vehicle {
private:
    // private so other code can't change these directly
    std::string vehicleNumber;
    std::string vehicleType;
    std::string ownerName;

public:
    Vehicle() = default;
    Vehicle(std::string number, std::string type, std::string owner);

    // prints the vehicle details, const since it doesn't change anything
    void displayVehicle() const;

    // getters, return const ref to avoid copying the string
    const std::string& getVehicleNumber() const { return vehicleNumber; }
    const std::string& getVehicleType() const { return vehicleType; }
    const std::string& getOwnerName() const { return ownerName; }
};

#endif