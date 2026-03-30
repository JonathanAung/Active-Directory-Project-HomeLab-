#include "LoginAttempt.h"
#include <iostream>

// Constructor: store all the fields
LoginAttempt::LoginAttempt(std::string user, std::string ip, std::string time, bool succeeded) {
    // TODO: assign each parameter to its matching member variable

}

// Print this attempt as one line
// Example: [FAIL] 2024-01-15 10:32:01 | User: jsmith | IP: 192.168.10.5
// Use [FAIL] for failed attempts and [OK] for successful ones
void LoginAttempt::print() const {
    // TODO: print success/fail tag, timestamp, username, and IP

}
