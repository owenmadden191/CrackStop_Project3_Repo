#include <chrono>//to measure clock time
#include <iostream>
#include <string>
#include "hashclass.h"

using namespace std;

int main() {

    hashclass poop;
    poop.readData("100000-most-common-passwords.txt");
    auto searchresult = poop.search("test");
    cout << searchresult.first << " " <<  endl;
    cout << searchresult.second << " nanoseconds" << endl;
    poop.clearvec();

    return 0;
}