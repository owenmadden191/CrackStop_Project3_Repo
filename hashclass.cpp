#include "hashclass.h"
#include <fstream>

hashclass::hashclass() : loadfactor(0.8), count(0.0), hashtable(100) {}

int hashclass::hashFun(const string& pass) const {
    // Simple additive hash; index is computed as hash % table_size
    int h = 0;
    for (unsigned char c : pass) {
        h += static_cast<int>(c);
    }
    if (h < 0) h = -h;
    return h;
}

void hashclass::insert(const string& pass) {
    if (hashtable.empty()) {
        hashtable.resize(100);
    }

    double currentLoadFactor = 0.0;
    if (!hashtable.empty()) {
        currentLoadFactor = count / static_cast<double>(hashtable.size());
    }
    if (currentLoadFactor > loadfactor) {
        rehash();
    }

    int index = hashFun(pass) % static_cast<int>(hashtable.size());
    hashtable[index].push_front(pass);
    ++count;
}

pair<bool, int64_t> hashclass::search(const string& pass) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    if (hashtable.empty()) {
        auto end = high_resolution_clock::now();
        auto time = duration_cast<nanoseconds>(end - start);
        return make_pair(false, time.count());
    }

    int index = hashFun(pass) % static_cast<int>(hashtable.size());
    bool present = false;

    const List& bucket = hashtable[index];
    unsigned int n = bucket.getNodeCount();
    for (unsigned int i = 0; i < n; ++i) {
        Node* node = bucket.getNode(i);
        if (node != nullptr && node->data == pass) {
            present = true;
            break;
        }
    }

    auto end = high_resolution_clock::now();
    auto time = duration_cast<nanoseconds>(end - start);
    return make_pair(present, time.count());
}

void hashclass::clearvec() {
    for (auto& lst : hashtable) {
        lst = List();
    }
    count = 0.0;
}

void hashclass::rehash() {
    // Double the table size and re-insert all elements
    size_t newSize = hashtable.empty() ? 100 : hashtable.size() * 2;
    vector<List> newTable(newSize);

    for (const auto& bucket : hashtable) {
        unsigned int n = bucket.getNodeCount();
        for (unsigned int i = 0; i < n; ++i) {
            Node* node = bucket.getNode(i);
            if (node != nullptr) {
                const string& val = node->data;

                int h = 0;
                for (unsigned char c : val) {
                    h += static_cast<int>(c);
                }
                if (h < 0) h = -h;
                int index = h % static_cast<int>(newSize);

                newTable[index].push_front(val);
            }
        }
    }

    hashtable.swap(newTable);
}

void hashclass::printtable() const {
    for (size_t i = 0; i < hashtable.size(); ++i) {
        const List& bucket = hashtable[i];
        unsigned int n = bucket.getNodeCount();
        if (n == 0) continue;

        cout << "Bucket " << i << ": ";
        for (unsigned int j = 0; j < n; ++j) {
            Node* node = bucket.getNode(j);
            if (node != nullptr) {
                cout << node->data << " ";
            }
        }
        cout << "\n";
    }
}

void hashclass::readData(const string& filename) {
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