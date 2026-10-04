#ifndef TICKET_H
#define TICKET_H

#include "Vehicle.h"

// stores the parking and billing details of a vehicle
class Ticket {
private:
    int ticketNumber;
    Vehicle* vehicle;   // non-owning pointer; Ticket does not delete this
    int slotNumber;
    double fee;

public:
    // creates a ticket for a parked vehicle
    Ticket(int number, Vehicle* v, int slot, double parkingFee);

    // displays the ticket details
    void displayTicket() const;

    // getters
    int getTicketNumber() const { return ticketNumber; }
    Vehicle* getVehicle() const { return vehicle; }
    int getSlotNumber() const { return slotNumber; }
    double getFee() const { return fee; }
};

#endif