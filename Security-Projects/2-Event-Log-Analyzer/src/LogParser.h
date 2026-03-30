#ifndef LOGPARSER_H
#define LOGPARSER_H

#include "LogEntry.h"
#include <vector>
#include <string>

// LogParser reads a CSV file full of Windows Event Log entries
// and turns each row into a LogEntry object.
// Think of it like a translator - it takes raw text and gives you usable data.

class LogParser {
private:
    std::vector<LogEntry> entries; // all the parsed log entries go here

public:
    // Reads the CSV file at the given path and fills the entries vector
    void parseCSV(std::string filename);

    // Returns all the parsed entries
    std::vector<LogEntry> getEntries() const;

    // Prints every entry to the terminal
    void printAll() const;
};

#endif
