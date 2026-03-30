#ifndef SCANNER_H
#define SCANNER_H

#include "Target.h"
#include <string>

// The Scanner class does the actual port scanning work.
// It tries to connect to each port on the target IP.
// If a connection succeeds, that port is open.
// Think of it like knocking on every door in a building to see which ones open.

class Scanner {
private:
    int timeoutSeconds; // how long to wait for a response before moving on

public:
    // Constructor: sets the timeout (default 1 second is fine to start)
    Scanner(int timeout = 1);

    // Tries to connect to one specific port on the given IP.
    // Returns true if the port is open, false if it is closed or filtered.
    // Hint: you will use socket(), connect(), and close() from <sys/socket.h>
    bool scanPort(std::string ip, int port);

    // Scans a range of ports on the target and stores open ones in the Target object
    // Hint: loop from startPort to endPort and call scanPort() each time
    void scanRange(Target& target, int startPort, int endPort);
};

#endif
