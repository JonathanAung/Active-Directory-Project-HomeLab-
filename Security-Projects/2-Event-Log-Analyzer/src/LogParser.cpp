#include "LogParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

// parseCSV reads each line of the CSV file and creates a LogEntry from it.
// The CSV format is: EventID,Timestamp,Username,IPAddress,Description
// Hint: use std::ifstream to open the file, std::getline to read lines,
// and std::stringstream + std::getline with a comma delimiter to split each line.
void LogParser::parseCSV(std::string filename) {
    // TODO: open the file using std::ifstream
    // TODO: if the file fails to open, print an error and return
    // TODO: skip the first line (it's the header row)
    // TODO: for each remaining line:
    //         - use a stringstream to split by comma
    //         - parse out: eventID (int), timestamp, username, ipAddress, description
    //         - create a LogEntry and push it into entries

}

std::vector<LogEntry> LogParser::getEntries() const {
    // TODO: return entries

}

void LogParser::printAll() const {
    // TODO: loop through entries and call print() on each one

}
