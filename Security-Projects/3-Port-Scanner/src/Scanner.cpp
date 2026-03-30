#include "Scanner.h"
#include <iostream>

// Linux socket headers - this is how C++ talks to the network
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Constructor
Scanner::Scanner(int timeout) {
    // TODO: assign timeout to timeoutSeconds

}

// Try to connect to one port on the given IP.
// Returns true if the connection succeeds (port is open), false if it fails.
//
// How sockets work (simplified):
//   1. socket()  - create a "phone"
//   2. connect() - try to call the number (ip + port)
//   3. If connect() returns 0, someone picked up = port is open
//   4. close()   - hang up
//
// Hint: use struct sockaddr_in to build the address
//       use AF_INET and SOCK_STREAM for a TCP connection
//       use inet_addr(ip.c_str()) to convert the IP string
//       use htons(port) to convert the port number
bool Scanner::scanPort(std::string ip, int port) {
    // TODO: create a socket using socket(AF_INET, SOCK_STREAM, 0)
    // TODO: if socket creation fails (returns -1), return false
    // TODO: fill in a sockaddr_in struct with the IP and port
    // TODO: call connect() - if it returns 0, the port is open
    // TODO: close the socket
    // TODO: return true if open, false if closed

}

// Scan a range of ports on the target and add open ones to the Target object
void Scanner::scanRange(Target& target, int startPort, int endPort) {
    std::cout << "Scanning " << target.getIP() << " ports " << startPort << " to " << endPort << "...\n";

    // TODO: loop from startPort to endPort (inclusive)
    // TODO: call scanPort() for each one
    // TODO: if it returns true, call target.addOpenPort() and print that the port is open

}
