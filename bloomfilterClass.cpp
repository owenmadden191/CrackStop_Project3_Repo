#include "bloomfilterClass.h"

bloomfilterClass::bloomfilterClass() {
    size_bf = 2000000;                 // size of the Bloom filter bit array
    bloomfilter.assign(size_bf, false);
}

vector<long long> bloomfilterClass::hashFun(const string& pass) {
    // Use 7 different prime seeds to generate 7 hash values
    int primes[7] = {3, 5, 7, 11, 13, 17, 19};
    vector<long long> finHash;
    finHash.reserve(7);

    for (int i = 0; i < 7; ++i) {
        long long h = primes[i];
        for (unsigned char c : pass) {
            h = h * 131 + static_cast<int>(c);
        }
        if (h < 0) h = -h;
        finHash.push_back(h);
    }
    return finHash;
}

vector<long long> bloomfilterClass::hashIndex(const vector<long long>& hashcode) {
    vector<long long> indexes;
    indexes.reserve(hashcode.size());
    for (long long h : hashcode) {
        indexes.push_back(h % size_bf);
    }
    return indexes;
}

void bloomfilterClass::insert(const string& pass) {
    vector<long long> hashcode = hashFun(pass);
    vector<long long> indexes = hashIndex(hashcode);

    for (long long idx : indexes) {
        bloomfilter[static_cast<size_t>(idx)] = true;
    }
}

void bloomfilterClass::readData(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        return;
    }

    string line;
    while (std::getline(inFile, line)) {
        // Trim trailing carriage returns and whitespace so that
        // lines from the file match user input exactly.
        while (!line.empty() &&
               (line.back() == '\r' || line.back() == ' ' || line.back() == '\t')) {
            line.pop_back();
        }

        if (!line.empty()) {
            insert(line);
        }
    }
}

pair<bool, int64_t> bloomfilterClass::search(const string& pass) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    vector<long long> hashcode = hashFun(pass);
    vector<long long> indexes = hashIndex(hashcode);

    bool present = true;
    for (long long idx : indexes) {
        if (!bloomfilter[static_cast<size_t>(idx)]) {
            present = false;
            auto end = high_resolution_clock::now();
            auto time = duration_cast<nanoseconds>(end - start);
            return make_pair(present, time.count());
        }
    }

    auto end = high_resolution_clock::now();
    auto time = duration_cast<nanoseconds>(end - start);
    return make_pair(present, time.count());
}
