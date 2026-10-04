#include "../include/ParkingSlot.h"
#include <iostream>

// Creates an empty parking slot
ParkingSlot::ParkingSlot()
    : slotNumber(0), occupied(false), vehicle(nullptr) {
}

// Creates a parking slot with the given slot number
ParkingSlot::ParkingSlot(int number)
    : slotNumber(number), occupied(false), vehicle(nullptr) {
}

// Assigns a vehicle to this parking slot
void ParkingSlot::assignVehicle(Vehicle* v) {
    vehicle = v;
    occupied = true;
}

// Removes the vehicle from the parking slot
void ParkingSlot::releaseSlot() {
    vehicle = nullptr;
    occupied = false;
}

// Shows the current status of the parking slot
void ParkingSlot::displaySlot() const {
     std::cout << "\n===== Parking Slot =====\n";
    std::cout << "Slot Number : " << slotNumber << '\n';
    std::cout << "Status      : "
              << (occupied ? "Occupied" : "Available") << '\n';

    if (occupied && vehicle != nullptr) {
        std::cout << "Vehicle     : "
                  << vehicle->getVehicleNumber() << '\n';
    }

    std::cout << "========================\n";
}

 