#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <fstream>

#include "hashclass.h"
#include "bloomfilterClass.h"

using namespace std;

struct CheckResults {
    bool lengthOK;
    bool charTypesOK;
    bool usernameNotInPass;
    bool notCommonPassword;
    bool passwordsMatch;
};

// Evaluate a password against all requirements except
// the common-password check, which is passed in.
CheckResults evaluatePassword(const string& username,
                              const string& password,
                              const string& confirm,
                              bool notCommonFromData) {
    CheckResults res{};

    // Length requirement
    res.lengthOK = password.length() >= 8;

    // Character-type requirement
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbol = false;
    for (unsigned char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSymbol = true;
    }
    res.charTypesOK = hasUpper && hasLower && hasDigit && hasSymbol;

    // Username not contained in password (case-insensitive)
    string userLower = username;
    string passLower = password;
    for (char& c : userLower) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    for (char& c : passLower) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

    if (!userLower.empty() && passLower.find(userLower) != string::npos) {
        res.usernameNotInPass = false;
    } else {
        res.usernameNotInPass = true;
    }

    // Common-password flag comes from data structure search
    res.notCommonPassword = notCommonFromData;

    // Confirmation
    res.passwordsMatch = (password == confirm);

    return res;
}

int main() {
    const string filename = "100000-most-common-passwords.txt";

    // Build data structures once from the common-password file.
    hashclass myHashtable;
    bloomfilterClass myBloom;

    myHashtable.clearvec();
    myHashtable.readData(filename);
    myBloom.readData(filename);

    bool keepRunning = true;

    while (keepRunning) {
        cout << "=============================================\n";
        cout << "                 Create New User             \n";
        cout << "=============================================\n\n";

        string username, password, confirm;

        cout << "Username: ";
        getline(cin, username);

        cout << "\nPassword Requirements:\n";
        cout << "  - At least 8 characters\n";
        cout << "  - Includes uppercase, lowercase, number, and symbol\n";
        cout << "  - Does not include username\n";
        cout << "  - Not a common password (from 100,000 list)\n\n";

        cout << "Password: ";
        getline(cin, password);

        cout << "Confirm Password: ";
        getline(cin, confirm);

        // Search both data structures and record their times.
        auto hashSearch  = myHashtable.search(password);
        auto bloomSearch = myBloom.search(password);

        bool isCommon = hashSearch.first;
        bool notCommon = !isCommon;

        CheckResults res = evaluatePassword(username, password, confirm, notCommon);

        bool allOK = res.lengthOK &&
                     res.charTypesOK &&
                     res.usernameNotInPass &&
                     res.notCommonPassword &&
                     res.passwordsMatch;

        if (allOK) {
            // Add this approved password to the in-memory "banned" sets
            myHashtable.insert(password);
            myBloom.insert(password);

            // Also append to the common-password file so it persists across runs.
            ofstream outFile(filename, ios::app);
            if (outFile.is_open()) {
                outFile << password << "\n";
            }
        }

        cout << "\n=============================================\n";
        cout << "                 Analysis Results            \n";
        cout << "=============================================\n\n";

        auto printCheck = [](const string& label, bool ok) {
            cout << "  " << (ok ? "[Y] " : "[N] ") << label << '\n';
        };

        printCheck("Length >= 8", res.lengthOK);
        printCheck("Includes uppercase, lowercase, number, and symbol", res.charTypesOK);
        printCheck("Does not contain username", res.usernameNotInPass);
        printCheck("Not found in common password list", res.notCommonPassword);
        printCheck("Password matches confirmation", res.passwordsMatch);
        cout << '\n';

        if (allOK) {
            cout << "Verdict: ACCEPTED\n";
            cout << "Reason:\n";
            cout << "  - All requirements satisfied.\n";
            cout << "Suggestion:\n";
            cout << "  - Keep this password private and avoid reusing it on other sites.\n";
        } else {
            cout << "Verdict: REJECTED\n";
            cout << "Reasons:\n";
            if (!res.lengthOK)
                cout << "  - Password is too short (must be at least 8 characters).\n";
            if (!res.charTypesOK)
                cout << "  - Password must include uppercase, lowercase, number, and symbol.\n";
            if (!res.usernameNotInPass)
                cout << "  - Password must not contain the username.\n";
            if (!res.notCommonPassword)
                cout << "  - Password is in the list of 100,000 most common passwords.\n";
            if (!res.passwordsMatch)
                cout << "  - Password and confirmation do not match.\n";

            cout << "\nSuggestions:\n";
            cout << "  - Try mixing random words with numbers and symbols.\n";
            cout << "  - Avoid dictionary words, names, or predictable patterns.\n";
        }

        cout << "\nPerformance (nanoseconds):\n";
        cout << "  Hash table search time : " << hashSearch.second  << " ns\n";
        cout << "  Bloom filter search time: " << bloomSearch.second << " ns\n";

        cout << "\n=============================================\n";
        cout << "              End of Analysis                \n";
        cout << "=============================================\n";

        // Ask if the user wants to run another test.
        cout << "\nWould you like to test another user/password? (y/n): ";
        char choice;
        if (!(cin >> choice)) {
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice != 'y' && choice != 'Y') {
            keepRunning = false;
        }

        cout << "\n\n";  // spacing before next loop iteration
    }

    return 0;
}
