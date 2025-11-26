#include "PasswordManager.h"
#include <fstream>
#include <cctype>
#include <iostream>

bool PasswordManager::loadBannedPasswords(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (!line.empty()) {
            bannedPasswords.insert(line);
        }
    }
    return true;
}

bool PasswordManager::userExists(const std::string& username) const {
    return userPasswordDB.find(username) != userPasswordDB.end();
}

bool PasswordManager::addNewPassword(const std::string& username,
                                     const std::string& password,
                                     std::string& errorMessage) {
    if (!meetsComplexityRequirements(password, username, errorMessage)) {
        return false;
    }

    if (isBannedPassword(password)) {
        errorMessage = "Password is too common or previously used.";
        return false;
    }

    std::string hashed = hashPassword(password);
    userPasswordDB[username] = hashed;

    bannedPasswords.insert(password);

    errorMessage.clear();
    return true;
}


bool PasswordManager::meetsComplexityRequirements(const std::string& password,
                                                  const std::string& username,
                                                  std::string& reason) const {
    if (password.length() < 8) {
        reason = "Password must be at least 8 characters long.";
        return false;
    }

    bool hasLower = false;
    bool hasUpper = false;
    bool hasDigit = false;
    bool hasSymbol = false;

    for (unsigned char c : password) {
        if (std::islower(c))      hasLower = true;
        else if (std::isupper(c)) hasUpper = true;
        else if (std::isdigit(c)) hasDigit = true;
        else                      hasSymbol = true;
    }

    if (!hasLower) {
        reason = "Password must contain at least one lowercase letter.";
        return false;
    }
    if (!hasUpper) {
        reason = "Password must contain at least one uppercase letter.";
        return false;
    }
    if (!hasDigit) {
        reason = "Password must contain at least one digit.";
        return false;
    }
    if (!hasSymbol) {
        reason = "Password must contain at least one symbol.";
        return false;
    }

    if (!username.empty()) {
        if (password.find(username) != std::string::npos) {
            reason = "Password must not contain the username.";
            return false;
        }
    }

    reason.clear();
    return true;
}

bool PasswordManager::isBannedPassword(const std::string& password) const {
    return bannedPasswords.find(password) != bannedPasswords.end();
}


std::string PasswordManager::hashPassword(const std::string& password) const {
    std::hash<std::string> hasher;
    size_t h = hasher(password);
    return std::to_string(h);
}

void PasswordManager::printDatabase() const {
    std::cout << "=== Stored Users (username : hashed password) ===\n";
    for (const auto& entry : userPasswordDB) {
        std::cout << entry.first << " : " << entry.second << "\n";
    }
}
