#ifndef PARKING_LOT_H
#define PARKING_LOT_H

#include "ParkingSlot.h"
#include <vector>

// Manages all parking slots
class ParkingLot {
private:
    // Stores all the parking slots in the parking lot
    std::vector<ParkingSlot> parkingSlots;

public:
    // Creates the parking lot
    ParkingLot(int numberOfSlots);

    // Parks a vehicle in the first available slot
    bool parkVehicle(Vehicle* vehicle);
    
    // Restores a vehicle into a specific slot when loading saved data
    bool parkVehicleInSlot(Vehicle* vehicle, int slotNumber);


    // Removes a vehicle from a slot
    bool removeVehicle(int slotNumber);

    // Finds which slot a vehicle is using
    int findVehicleSlot(Vehicle* vehicle) const;

    // Displays all slots
    void displayAllSlots() const;

    // Returns total number of slots
    int getTotalSlots() const {
        return static_cast<int>(parkingSlots.size());
    }
};

#endif

