#ifndef DETECTIONENGINE_H
#define DETECTIONENGINE_H

#include "LoginAttempt.h"
#include <vector>
#include <string>
#include <map>

// DetectionEngine is the brain of the detector.
// It takes a list of login attempts and looks for suspicious patterns.
// This is basically what Splunk does automatically - you're building it from scratch.

class DetectionEngine {
private:
    std::vector<LoginAttempt> attempts; // all the login attempts loaded from the log file

    // threshold: how many failures before we fire an alert
    int failureThreshold;

public:
    // Constructor: set the threshold (default 5 failures = suspicious)
    DetectionEngine(int threshold = 5);

    // Load all login attempts from a log file
    void loadAttempts(std::string filename);

    // Check for brute force by username:
    // if the same username has more failed attempts than the threshold, alert
    void checkByUsername() const;

    // Check for brute force by IP address:
    // if the same IP has more failed attempts than the threshold, alert
    void checkByIP() const;

    // Prints a summary of all attempts (total, failed, successful)
    void printSummary() const;

    // Runs all checks
    void runAll() const;
};

#endif
