#ifndef HASHCLASS_H
#define HASHCLASS_H

#include "List.h"
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <chrono>

using namespace std;

class hashclass {
public:
    hashclass();

    int hashFun(const string& pass) const;

    void insert(const string& pass);
    void clearvec();
    void rehash();
    void printtable() const;
    void readData(const string& filename);
    pair<bool, int64_t> search(const string& pass);

private:
    double loadfactor;
    double count;
    vector<List> hashtable;
};

#endif