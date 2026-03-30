#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <vector>

// The Password class takes a string input and analyzes how strong it is.
// It checks for length, uppercase, lowercase, numbers, and special characters,
// then gives back a score, a rating, and feedback on what to improve.

class Password {
private:
    std::string value;      // the actual password string the user typed in
    int score;              // the strength score out of 100
    std::vector<std::string> feedback; // list of suggestions to improve the password

    // Private helper methods - these do one check each and return true or false
    bool hasUppercase() const;    // does it have at least one A-Z?
    bool hasLowercase() const;    // does it have at least one a-z?
    bool hasDigit() const;        // does it have at least one 0-9?
    bool hasSpecialChar() const;  // does it have at least one !@#$ etc?
    bool isLongEnough() const;    // is it 8+ characters?
    bool isVeryLong() const;      // is it 16+ characters?

public:
    // Constructor: takes the password string as input
    Password(std::string input);

    void analyze();                        // runs all checks, builds score and feedback
    int getScore() const;                  // returns the score (0-100)
    std::string getRating() const;         // returns "Weak", "Fair", "Strong", or "Very Strong"
    std::vector<std::string> getFeedback() const; // returns the list of suggestions
    void printReport() const;             // prints the full report to the terminal
};

#endif
