#ifndef BILLING_H
#define BILLING_H

#include <string>

// handles parking fee calculation
class Billing {
public:
    // calculates the parking fee based on duration
    static double calculateFee(int hours);

    // shows the fee details
    static void displayBill(double fee, int hours);
};

#endif