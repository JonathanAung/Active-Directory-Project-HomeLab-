#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>

// A LogEntry represents one single row from a Windows Event Log CSV export.
// Every time something happens on a Windows machine (login, logout, account created),
// Windows writes an event. This class stores the data from one of those events.

class LogEntry {
public:
    int eventID;          // the event code - tells us what happened (4625 = failed login, etc.)
    std::string timestamp; // when it happened
    std::string username;  // which account was involved
    std::string ipAddress; // where it came from (if available)
    std::string description; // a plain text description of the event

    // Constructor: takes all five fields and stores them
    LogEntry(int id, std::string time, std::string user, std::string ip, std::string desc);

    // Prints this log entry as one line to the terminal
    void print() const;
};

#endif
