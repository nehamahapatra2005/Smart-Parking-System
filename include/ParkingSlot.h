#ifndef PARKING_SLOT_H
#define PARKING_SLOT_H

#include "Vehicle.h"

// stores information about one parking slot
class ParkingSlot {
private:
    int slotNumber;
    bool occupied;
    Vehicle* vehicle;

public:
    // default constructor
    ParkingSlot();

    // creates a slot with a given slot number
    ParkingSlot(int number);

    // assigns a vehicle to the slot
    void assignVehicle(Vehicle* v);

    // removes the vehicle from the slot
    void releaseSlot();

    // displays the current slot details
    void displaySlot() const;

    // getters
    int getSlotNumber() const { return slotNumber; }
    bool isOccupied() const { return occupied; }
    Vehicle* getVehicle() const { return vehicle; }
};

#endif
