#include "../include/Billing.h"
#include <iostream>
#include <iomanip>

// Calculates the parking fee
double Billing::calculateFee(int hours) {

    const double hourlyRate = 20.0;

    if (hours <= 0) {
        return 0.0;
    }

    return hours * hourlyRate;
}

// Displays the parking bill
void Billing::displayBill(double fee, int hours) {

    std::cout << "\n";
    std::cout << "+----------------------------------+\n";
    std::cout << "|           PARKING BILL           |\n";
    std::cout << "+----------------------------------+\n";

    std::cout << "| Duration      : " << std::setw(14)
              << std::left << hours << "|\n";

    std::cout << "| Hourly Rate   : Rs." << std::setw(11)
              << std::left << "20.00" << "|\n";

    std::cout << "| Total Fee     : Rs." << std::setw(11)
              << std::left << std::fixed << std::setprecision(2)
              << fee << "|\n";

    std::cout << "+----------------------------------+\n";
}