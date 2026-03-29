#include "Password.h"
#include <iostream>
#include <cctype>

// Constructor: store the password and set score to 0 to start
Password::Password(std::string input) {
    value = input;
    score = 0;
}

// Check if the password has at least one uppercase letter
bool Password::hasUppercase() const {
    for (char c : value) {
        if (std::isupper(c)) return true;
    }
    return false;
}

// Check if the password has at least one lowercase letter
bool Password::hasLowercase() const {
    for (char c : value) {
        if (std::islower(c)) return true;
    }
    return false;
}

// Check if the password has at least one number
bool Password::hasDigit() const {
    for (char c : value) {
        if (std::isdigit(c)) return true;
    }
    return false;
}

// Check if the password has at least one special character
bool Password::hasSpecialChar() const {
    std::string specialChars = "!@#$%^&*()-_=+[]{}|;:',.<>?/`~";
    for (char c : value) {
        if (specialChars.find(c) != std::string::npos) return true;
    }
    return false;
}

// Minimum length is 8 characters
bool Password::isLongEnough() const {
    return value.length() >= 8;
}

// 16+ characters is considered very long (bonus points)
bool Password::isVeryLong() const {
    return value.length() >= 16;
}

// analyze() runs all the checks, builds the score, and collects feedback
void Password::analyze() {
    score = 0;
    feedback.clear();

    // Length checks
    if (isVeryLong()) {
        score += 30;
    } else if (isLongEnough()) {
        score += 15;
    } else {
        feedback.push_back("Use at least 8 characters (16+ is much stronger)");
    }

    // Uppercase check
    if (hasUppercase()) {
        score += 20;
    } else {
        feedback.push_back("Add at least one uppercase letter (A-Z)");
    }

    // Lowercase check
    if (hasLowercase()) {
        score += 20;
    } else {
        feedback.push_back("Add at least one lowercase letter (a-z)");
    }

    // Number check
    if (hasDigit()) {
        score += 15;
    } else {
        feedback.push_back("Add at least one number (0-9)");
    }

    // Special character check
    if (hasSpecialChar()) {
        score += 15;
    } else {
        feedback.push_back("Add at least one special character (!@#$%^&* etc.)");
    }

    // Cap the score at 100
    if (score > 100) score = 100;
}

int Password::getScore() const {
    return score;
}

// Rating is based on the score
std::string Password::getRating() const {
    if (score >= 85) return "Very Strong";
    if (score >= 65) return "Strong";
    if (score >= 40) return "Fair";
    return "Weak";
}

std::vector<std::string> Password::getFeedback() const {
    return feedback;
}

// printReport() displays everything nicely in the terminal
void Password::printReport() const {
    std::cout << "\n==========================================\n";
    std::cout << "  PASSWORD STRENGTH REPORT\n";
    std::cout << "==========================================\n";
    std::cout << "  Score  : " << score << " / 100\n";
    std::cout << "  Rating : " << getRating() << "\n";

    if (feedback.empty()) {
        std::cout << "  Status : No issues found. Looks good!\n";
    } else {
        std::cout << "\n  Suggestions to improve:\n";
        for (const std::string& tip : feedback) {
            std::cout << "   - " << tip << "\n";
        }
    }

    std::cout << "==========================================\n\n";
}
