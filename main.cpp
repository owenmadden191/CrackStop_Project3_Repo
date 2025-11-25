#include <chrono>//to measure clock time
#include <iostream>
#include <string>
#include "hashclass.h"
#include "bloomfilterClass.h"

using namespace std;

int main() {
    string test = "123456";

    hashclass myhashtable;
    myhashtable.readData("../../../100000-most-common-passwords.txt");
    auto hashtableSearch = myhashtable.search(test);
    myhashtable.clearvec();

    bloomfilterClass mybloomfilter;
    mybloomfilter.readData("../../../100000-most-common-passwords.txt");
    auto bloomSearch = mybloomfilter.search(test);


    if (hashtableSearch.first) {
        cout << "hash table found " << test << ", took " << hashtableSearch.second << " ns." << endl;
        cout << "bloom filter found " << test << ", took " << bloomSearch.second << " ns." << endl;
    }
    else {
        cout << "hashtable couldn't find " << test << ", took " << hashtableSearch.second << " ns." << endl;
        if (bloomSearch.first) { //false positive
            cout << "FALSE POSITIVE. Bloom filter found " << test << ", took " << bloomSearch.second << " ns." << endl;
        }
        else {
            cout << "bloom filter couldn't find " << test << ", took " << bloomSearch.second << " ns." << endl;
        }
    }

    return 0;
}