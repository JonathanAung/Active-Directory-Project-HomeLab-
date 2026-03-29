#include "AlertEngine.h"
#include <iostream>
#include <map>

// Constructor: store the entries and threshold
AlertEngine::AlertEngine(std::vector<LogEntry> logEntries, int threshold) {
    // TODO: assign logEntries to entries and threshold to bruteForceThreshold

}

// Look for Event ID 4720 (new user account created) - always suspicious, always alert
void AlertEngine::checkNewAccounts() const {
    std::cout << "\n[CHECK] Scanning for new account creation (Event ID 4720)...\n";

    // TODO: loop through entries
    // TODO: if eventID == 4720, print an alert showing the username, timestamp, and IP

}

// Look for Event ID 4732 (user added to privileged group) - possible privilege escalation
void AlertEngine::checkPrivilegeEscalation() const {
    std::cout << "\n[CHECK] Scanning for privilege escalation (Event ID 4732)...\n";

    // TODO: loop through entries
    // TODO: if eventID == 4732, print an alert

}

// Count failed logins (Event ID 4625) per username.
// If any username exceeds the threshold, print a brute force alert.
// Hint: use a std::map<std::string, int> to count failures per username
void AlertEngine::checkBruteForce() const {
    std::cout << "\n[CHECK] Scanning for brute force logins (Event ID 4625, threshold: "
              << bruteForceThreshold << ")...\n";

    // TODO: create a map to count 4625 events per username
    // TODO: loop through entries - if eventID == 4625, increment that username's count
    // TODO: loop through the map - if count >= threshold, print an alert

}

// Run all checks
void AlertEngine::runAll() const {
    checkNewAccounts();
    checkPrivilegeEscalation();
    checkBruteForce();
}
