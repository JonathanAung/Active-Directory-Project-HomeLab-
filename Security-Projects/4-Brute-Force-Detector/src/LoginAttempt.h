#ifndef LOGINATTEMPT_H
#define LOGINATTEMPT_H

#include <string>

// A LoginAttempt represents one single login event from a log file.
// This mirrors what you saw in Splunk during the AD HomeLab -
// every failed login (Event ID 4625) is one of these.

class LoginAttempt {
public:
    std::string username;   // the account that was targeted
    std::string ipAddress;  // where the attempt came from
    std::string timestamp;  // when it happened
    bool success;           // true = logged in, false = failed

    // Constructor
    LoginAttempt(std::string user, std::string ip, std::string time, bool succeeded);

    // Prints this attempt as one line
    void print() const;
};

#endif
