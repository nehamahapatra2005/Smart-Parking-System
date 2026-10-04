#include "../include/Vehicle.h"
#include "../include/ParkingLot.h"
#include "../include/Ticket.h"
#include "../include/Billing.h"

#include <iostream>
#include <vector>
#include <string>

// Displays the main menu
void showMenu() {
    std::cout << "\n";
    std::cout << "+======================================+\n";
    std::cout << "|        SMART PARKING SYSTEM          |\n";
    std::cout << "+======================================+\n";
    std::cout << "|  1. Park Vehicle                     |\n";
    std::cout << "|  2. View Parking Slots               |\n";
    std::cout << "|  3. Checkout Vehicle                 |\n";
    std::cout << "|  4. Search Vehicle                   |\n";
    std::cout << "|  5. Exit                             |\n";
    std::cout << "+======================================+\n";
    std::cout << "Enter your choice: ";
}

int main() {

    // Create a parking lot with 5 slots
    ParkingLot parkingLot(5);

    // Stores vehicles while the program is running
    std::vector<Vehicle> vehicles;
    vehicles.reserve(100);

    int ticketNumber = 1001;
    int choice;

    while (true) {

        showMenu();
        std::cin >> choice;

        // Park a vehicle
        if (choice == 1) {

            std::string vehicleNumber;
            std::string vehicleType;
            std::string ownerName;

            std::cout << "\n--- Park Vehicle ---\n";

            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleNumber;

            std::cout << "Enter vehicle type: ";
            std::cin >> vehicleType;

            std::cout << "Enter owner name: ";
            std::cin >> ownerName;

            // Add the vehicle to our list
            vehicles.emplace_back(vehicleNumber, vehicleType, ownerName);

            Vehicle* vehicle = &vehicles.back();

            // Try to park the vehicle
            if (parkingLot.parkVehicle(vehicle)) {

                int slotNumber = parkingLot.findVehicleSlot(vehicle);

                // Create a basic parking ticket
                Ticket ticket(ticketNumber, vehicle, slotNumber, 0.0);

                std::cout << "\nTicket generated successfully!\n";
                ticket.displayTicket();

                ticketNumber++;
            }
            else {
                // Remove the vehicle if there was no parking space
                vehicles.pop_back();
            }
        }

        // View all parking slots
        else if (choice == 2) {

            parkingLot.displayAllSlots();
        }

        // Checkout a vehicle
        else if (choice == 3) {

            int slotNumber;
            int hours;

            std::cout << "\n--- Vehicle Checkout ---\n";

            std::cout << "Enter slot number: ";
            std::cin >> slotNumber;

            std::cout << "Enter parking duration (hours): ";
            std::cin >> hours;

            double fee = Billing::calculateFee(hours);

            // Display the bill
            Billing::displayBill(fee, hours);

            // Remove the vehicle
            if (parkingLot.removeVehicle(slotNumber)) {
                std::cout << "\nCheckout completed successfully!\n";
            }
        }

        // Search for a vehicle
        else if (choice == 4) {

            std::string vehicleNumber;
            bool found = false;

            std::cout << "\n--- Search Vehicle ---\n";
            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleNumber;

            for (Vehicle& vehicle : vehicles) {

                if (vehicle.getVehicleNumber() == vehicleNumber) {

                    int slotNumber =
                        parkingLot.findVehicleSlot(&vehicle);

                    if (slotNumber != -1) {

                        std::cout << "\nVehicle found!\n";
                        std::cout << "Vehicle Number : "
                                  << vehicle.getVehicleNumber() << '\n';

                        std::cout << "Vehicle Type   : "
                                  << vehicle.getVehicleType() << '\n';

                        std::cout << "Owner Name     : "
                                  << vehicle.getOwnerName() << '\n';

                        std::cout << "Slot Number    : "
                                  << slotNumber << '\n';

                        found = true;
                    }
                }
            }

            if (!found) {
                std::cout << "\nVehicle is not currently parked.\n";
            }
        }

        // Exit the program
        else if (choice == 5) {

            std::cout << "\nThank you for using Smart Parking System!\n";
            break;
        }

        else {
            std::cout << "\nInvalid choice. Please try again.\n";
        }
    }

    return 0;
}