#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class bloomfilterClass {
public:
    bloomfilterClass();
    vector<long long> hashFun(string pass);
    vector<long long> hashIndex(vector<long long> hashcode);
    void insert(string pass);
    void readData(string filename);
    pair<bool, int64_t> search(string pass);
private:
    int size_bf;
    vector<bool> bloomfilter;
};

