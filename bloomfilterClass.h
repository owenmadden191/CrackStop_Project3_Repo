#ifndef BLOOMFILTERCLASS_H
#define BLOOMFILTERCLASS_H

#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class bloomfilterClass {
public:
    bloomfilterClass();

    vector<long long> hashFun(const string& pass);
    vector<long long> hashIndex(const vector<long long>& hashcode);
    void insert(const string& pass);
    void readData(const string& filename);
    pair<bool, int64_t> search(const string& pass);

private:
    int size_bf;
    vector<bool> bloomfilter;
};

#endif
