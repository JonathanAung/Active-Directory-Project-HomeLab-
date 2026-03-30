#include "Password.h"
#include <iostream>
#include <cctype>

// Constructor: store the password and set score to 0 to start
Password::Password(std::string input) {
    // TODO: assign input to value, set score to 0

}

// Return true if the password contains at least one uppercase letter (A-Z)
// Hint: loop through each character in value and use std::isupper(c)
bool Password::hasUppercase() const {
    // TODO

}

// Return true if the password contains at least one lowercase letter (a-z)
// Hint: use std::islower(c)
bool Password::hasLowercase() const {
    // TODO

}

// Return true if the password contains at least one digit (0-9)
// Hint: use std::isdigit(c)
bool Password::hasDigit() const {
    // TODO

}

// Return true if the password contains at least one special character
// Hint: make a string of special characters and use .find() to check
bool Password::hasSpecialChar() const {
    // TODO
    // std::string specialChars = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~";

}

// Return true if the password is 8 or more characters
// Hint: use value.length()
bool Password::isLongEnough() const {
    // TODO

}

// Return true if the password is 16 or more characters
bool Password::isVeryLong() const {
    // TODO

}

// analyze() runs all the checks above, builds the score, and fills the feedback vector
// Scoring guide:
//   16+ characters  = +30 points
//   8-15 characters = +15 points
//   has uppercase   = +20 points
//   has lowercase   = +20 points
//   has digit       = +15 points
//   has special     = +15 points
// If a check fails, push a helpful message into the feedback vector instead
void Password::analyze() {
    // TODO: reset score to 0 and clear feedback first
    // then run each check and add points or push feedback

}

// Return the score
int Password::getScore() const {
    // TODO

}

// Return a rating string based on the score
// 85-100 = "Very Strong", 65-84 = "Strong", 40-64 = "Fair", below 40 = "Weak"
std::string Password::getRating() const {
    // TODO

}

// Return the feedback vector
std::vector<std::string> Password::getFeedback() const {
    // TODO

}

// Print the full report to the terminal
// Show the score, rating, and each feedback suggestion
void Password::printReport() const {
    // TODO: use std::cout to print a nicely formatted report
    // Show score out of 100, the rating, and each item in feedback

}
