#include <chrono>//to measure clock time
#include <iostream>
#include <string>
#include "hashclass.h"

using namespace std;

int main() {

    hashclass myhashtable;
    myhashtable.readData("100000-most-common-passwords.txt");
    auto searchresult = myhashtable.search("test");
    cout << searchresult.first << " " <<  endl;
    cout << searchresult.second << " nanoseconds" << endl;
    myhashtable.clearvec();

    return 0;
}