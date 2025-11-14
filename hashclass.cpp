#include "hashclass.h"

hashclass::hashclass():hashtable(100){
    loadfactor = .8;
    count = 0.0;
};

//hashing function
int hashclass::hashFun(string pass) {
    int answer = 0;
    for (int i = 0; i < pass.length() ;i++) {
        int asciiValue =pass[i];
        answer += asciiValue;
    }
    return answer;
}

//creates index
int hashclass::hashindex(int hashcode) {
    return hashcode % hashtable.size();
}

//insert items into vector
void hashclass::insert(string pass) {
    int temp_pass = hashFun(pass);
    int index = hashindex(temp_pass);
    hashtable[index].push_front(pass);
    count++;
    double spaceut = count/hashtable.size();
    if (spaceut >= loadfactor) {
        rehash();
    }
}

void hashclass::clearvec() {
    hashtable.clear();
}

void hashclass::rehash() {
    vector<List> newhashtable(hashtable.size()*2);
    for (int i = 0; i < hashtable.size(); i ++) {
        for (int j = 0; j < hashtable[i].getNodeCount(); j++ ){
            if (hashtable[i].getNode(j) != nullptr) {
                int temp_pass = hashFun(hashtable[i].getNode(j)->data);
                int index = temp_pass%newhashtable.size();
                newhashtable[index].push_front(hashtable[i].getNode(j)->data);
            }
        }
    }
    hashtable=newhashtable;
}

void hashclass::printtable() { //prints out hashtable, only for debug
    cout << "size: " << hashtable.size() << endl;
    for (int i = 0; i < hashtable.size(); i ++) {
        for (int j = 0; j < hashtable[i].getNodeCount(); j++ ) {
            cout << i << " " << hashtable[i].getNode(j)->data << " ";
        }
        cout << endl;
    }
}

pair<bool,int64_t> hashclass::search(string pass) { //returns if present and lookup time in ns
    auto start = chrono::high_resolution_clock::now();
    int temp_pass = hashFun(pass);
    int index = hashindex(temp_pass);
    bool present = false;
    for (int j = 0; j < hashtable[index].getNodeCount(); j++ ) {
        if (hashtable[index].getNode(j)->data == pass) {
            present = true;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto time = duration_cast<chrono::nanoseconds>(end-start);
    return make_pair(present,time.count());
}
void hashclass::readData(string filename) {
    string linefromfile;
    ifstream inFile(filename);
    while (getline(inFile, linefromfile)) {
        insert(linefromfile);
    }
}