#include <iostream>
#include <string>
#include "Password.h"

int main() {
    std::string input;

    std::cout << "\n==========================================\n";
    std::cout << "       PASSWORD STRENGTH CHECKER\n";
    std::cout << "==========================================\n";
    std::cout << "Enter a password to check: ";
    std::cin >> input;

    // Create a Password object with the user's input
    Password p(input);

    // Run the analysis
    p.analyze();

    // Print the full report
    p.printReport();

    return 0;
}
