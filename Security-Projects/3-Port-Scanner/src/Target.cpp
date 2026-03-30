#include "Target.h"
#include <iostream>

// Constructor: store the IP address
Target::Target(std::string ip) {
    // TODO: assign ip to ipAddress

}

std::string Target::getIP() const {
    // TODO: return ipAddress

}

std::vector<int> Target::getOpenPorts() const {
    // TODO: return openPorts

}

// Add a port to the openPorts list
void Target::addOpenPort(int port) {
    // TODO: push port into the openPorts vector

}

// Print the scan results for this target
// Show the IP and list every open port
// If no ports are open, say so
void Target::printResults() const {
    // TODO: print the IP address
    // TODO: if openPorts is empty, print "No open ports found"
    // TODO: otherwise loop through openPorts and print each one

}
