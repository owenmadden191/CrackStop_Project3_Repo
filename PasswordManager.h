#ifndef PASSWORD_MANAGER_H
#define PASSWORD_MANAGER_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class PasswordManager {
public:
    PasswordManager() = default;

    bool loadBannedPasswords(const std::string& filename);

    bool userExists(const std::string& username) const;

    bool addNewPassword(const std::string& username,
                        const std::string& password,
                        std::string& errorMessage);

    void printDatabase() const;

private:
    bool meetsComplexityRequirements(const std::string& password,
                                     const std::string& username,
                                     std::string& reason) const;

    bool isBannedPassword(const std::string& password) const;

    std::string hashPassword(const std::string& password) const;

    std::unordered_map<std::string, std::string> userPasswordDB;

    std::unordered_set<std::string> bannedPasswords;
};

#endif
