#ifndef PASSWORD_H
#define PASSWORD_H

#include <string>
#include <vector>

// The Password class takes a string input and analyzes how strong it is.
// It checks for length, uppercase, lowercase, numbers, and special characters,
// then gives back a score, a rating, and feedback on what to improve.

class Password {
private:
    std::string value;
    int score;
    std::vector<std::string> feedback;

    // These are the individual checks we run
    bool hasUppercase() const;
    bool hasLowercase() const;
    bool hasDigit() const;
    bool hasSpecialChar() const;
    bool isLongEnough() const;
    bool isVeryLong() const;

public:
    Password(std::string input);

    void analyze();               // runs all the checks and builds the score
    int getScore() const;         // returns score out of 100
    std::string getRating() const; // returns "Weak", "Fair", "Strong", or "Very Strong"
    std::vector<std::string> getFeedback() const; // returns list of suggestions
    void printReport() const;     // prints everything to the terminal
};

#endif
