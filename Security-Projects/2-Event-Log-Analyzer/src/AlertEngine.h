#ifndef ALERTENGINE_H
#define ALERTENGINE_H

#include "LogEntry.h"
#include <vector>

// AlertEngine looks through all the parsed log entries and flags suspicious ones.
// This is the detection logic - it knows which Event IDs are dangerous
// and what patterns look like an attack.
//
// Event ID reference (from your AD HomeLab):
//   4625 = Failed login attempt
//   4624 = Successful login
//   4720 = A new user account was created
//   4732 = A user was added to a privileged group

class AlertEngine {
private:
    std::vector<LogEntry> entries; // the log entries to analyze
    int bruteForceThreshold;       // how many failed logins before we alert (default: 5)

public:
    // Constructor: takes the parsed entries and a threshold
    AlertEngine(std::vector<LogEntry> logEntries, int threshold = 5);

    // Flags any Event ID 4720 entries (new account created)
    void checkNewAccounts() const;

    // Flags any Event ID 4732 entries (user added to admin group)
    void checkPrivilegeEscalation() const;

    // Counts failed logins (4625) per username - alert if count exceeds threshold
    void checkBruteForce() const;

    // Runs all three checks above
    void runAll() const;
};

#endif
