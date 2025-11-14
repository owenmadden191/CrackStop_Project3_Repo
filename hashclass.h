#include "List.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>

class hashclass {
public:
    hashclass();
    int hashFun(string pass);
    int hashindex(int hashcode);
    void insert(string pass);
    void clearvec();
    void rehash();
    void printtable();
    //bool search(string pass);
    void readData(string filename);
    pair<bool,int64_t> search(string pass);
private:
    double loadfactor;
    double count;
    vector<List> hashtable;
};




