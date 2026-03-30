#include "DetectionEngine.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
DetectionEngine::DetectionEngine(int threshold) {
    // TODO: assign threshold to failureThreshold

}

// Load login attempts from a log file.
// The file format is: Username,IPAddress,Timestamp,Success(0 or 1)
// Hint: same approach as LogParser - use ifstream, getline, stringstream
void DetectionEngine::loadAttempts(std::string filename) {
    // TODO: open the file
    // TODO: if it fails to open, print an error and return
    // TODO: skip the header line
    // TODO: for each line, parse: username, ipAddress, timestamp, success (convert "1"/"0" to bool)
    // TODO: create a LoginAttempt and push it into attempts

}

// Check for brute force by username.
// Count how many times each username appears with success = false.
// If the count exceeds failureThreshold, print an alert.
// Hint: use a std::map<std::string, int> to count failures per username
void DetectionEngine::checkByUsername() const {
    std::cout << "\n[CHECK] Brute force by username (threshold: " << failureThreshold << " failures)\n";

    // TODO: create a map to count failed attempts per username
    // TODO: loop through attempts - for each failed one, increment that username's count
    // TODO: loop through the map - if any count >= failureThreshold, print an alert

}

// Check for brute force by IP address.
// Same logic as checkByUsername but grouped by IP instead.
void DetectionEngine::checkByIP() const {
    std::cout << "\n[CHECK] Brute force by IP address (threshold: " << failureThreshold << " failures)\n";

    // TODO: same as checkByUsername but use ipAddress as the map key

}

// Print a summary: total attempts, how many failed, how many succeeded
void DetectionEngine::printSummary() const {
    // TODO: count total, failed, and successful attempts from the vector
    // TODO: print each count

}

// Run everything
void DetectionEngine::runAll() const {
    printSummary();
    checkByUsername();
    checkByIP();
}
