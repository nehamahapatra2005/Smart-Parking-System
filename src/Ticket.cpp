#include "../include/Ticket.h"
#include <iostream>
#include <iomanip>

// Creates a ticket with vehicle, slot and parking fee
Ticket::Ticket(int number, Vehicle* v, int slot, double parkingFee)
    : ticketNumber(number),
      vehicle(v),
      slotNumber(slot),
      fee(parkingFee) {
}

// Displays the complete parking ticket
void Ticket::displayTicket() const {

    std::cout << "\n";
    std::cout << "╔══════════════════════════════════╗\n";
    std::cout << "║          PARKING TICKET          ║\n";
    std::cout << "╠══════════════════════════════════╣\n";

    std::cout << "║ Ticket Number : " << std::setw(15)
              << std::left << ticketNumber << "║\n";

    std::cout << "║ Vehicle No.   : " << std::setw(15)
              << std::left << vehicle->getVehicleNumber() << "║\n";

    std::cout << "║ Vehicle Type  : " << std::setw(15)
              << std::left << vehicle->getVehicleType() << "║\n";

    std::cout << "║ Owner Name    : " << std::setw(15)
              << std::left << vehicle->getOwnerName() << "║\n";

    std::cout << "║ Slot Number   : " << std::setw(15)
              << std::left << slotNumber << "║\n";

    std::cout << "║ Parking Fee   : Rs." << std::setw(11)
              << std::left << std::fixed << std::setprecision(2)
              << fee << "║\n";

    std::cout << "╠══════════════════════════════════╣\n";
    std::cout << "║       Thank you for parking!     ║\n";
    std::cout << "╚══════════════════════════════════╝\n";
}