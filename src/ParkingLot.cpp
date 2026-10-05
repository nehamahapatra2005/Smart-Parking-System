#include "../include/ParkingLot.h"
#include <iostream>

// Creates the required number of parking slots
ParkingLot::ParkingLot(int numberOfSlots) {

    for (int i = 1; i <= numberOfSlots; i++) {
        parkingSlots.push_back(ParkingSlot(i));
    }
}


// Finds the first available slot and parks the vehicle
bool ParkingLot::parkVehicle(Vehicle* vehicle) {

    for (ParkingSlot& slot : parkingSlots) {

        if (!slot.isOccupied()) {

            slot.assignVehicle(vehicle);

            std::cout << "\nVehicle parked successfully!\n";
            std::cout << "Assigned Slot : "
                      << slot.getSlotNumber() << '\n';

            return true;
        }
    }

    std::cout << "\nSorry, parking lot is full!\n";

    return false;
}


// Restores a vehicle into a specific slot
// Used when loading previously saved parking data
bool ParkingLot::parkVehicleInSlot(Vehicle* vehicle, int slotNumber) {

    for (ParkingSlot& slot : parkingSlots) {

        if (slot.getSlotNumber() == slotNumber &&
            !slot.isOccupied()) {

            slot.assignVehicle(vehicle);

            return true;
        }
    }

    return false;
}


// Removes a vehicle from the given slot
bool ParkingLot::removeVehicle(int slotNumber) {

    for (ParkingSlot& slot : parkingSlots) {

        if (slot.getSlotNumber() == slotNumber &&
            slot.isOccupied()) {

            slot.releaseSlot();

            std::cout << "\nVehicle removed successfully!\n";

            return true;
        }
    }

    std::cout << "\nNo vehicle found in this slot!\n";

    return false;
}


// Finds which slot a vehicle is using
int ParkingLot::findVehicleSlot(Vehicle* vehicle) const {

    for (const ParkingSlot& slot : parkingSlots) {

        if (slot.isOccupied() &&
            slot.getVehicle() == vehicle) {

            return slot.getSlotNumber();
        }
    }

    // -1 means the vehicle is not currently parked
    return -1;
}


// Displays all parking slots
void ParkingLot::displayAllSlots() const {

    std::cout << "\n===== Parking Lot Status =====\n";

    for (const ParkingSlot& slot : parkingSlots) {
        slot.displaySlot();
    }

    std::cout << "==============================\n";
}