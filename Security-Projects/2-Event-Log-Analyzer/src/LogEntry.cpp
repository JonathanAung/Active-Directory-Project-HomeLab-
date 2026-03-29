#include "LogEntry.h"
#include <iostream>

// Constructor: store all the fields passed in
LogEntry::LogEntry(int id, std::string time, std::string user, std::string ip, std::string desc) {
    // TODO: assign each parameter to its matching member variable

}

// Print this entry as one readable line
// Example output:  [4625] 2024-01-15 10:32:01 | User: jsmith | IP: 192.168.10.5 | Failed login attempt
void LogEntry::print() const {
    // TODO: use std::cout to print eventID, timestamp, username, ipAddress, and description

}
