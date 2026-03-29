#ifndef TARGET_H
#define TARGET_H

#include <string>
#include <vector>

// A Target represents one IP address we want to scan.
// After scanning, it stores the list of open ports we found.

class Target {
private:
    std::string ipAddress;       // the IP we are scanning
    std::vector<int> openPorts;  // ports that responded (meaning something is listening there)

public:
    // Constructor: takes an IP address string
    Target(std::string ip);

    // Getters
    std::string getIP() const;
    std::vector<int> getOpenPorts() const;

    // Adds a port number to the openPorts list
    void addOpenPort(int port);

    // Prints the scan results for this target
    void printResults() const;
};

#endif
