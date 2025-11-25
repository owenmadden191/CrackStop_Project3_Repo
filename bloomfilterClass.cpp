#include "bloomfilterClass.h"

bloomfilterClass::bloomfilterClass() {
	size_bf = 2000000;
	bloomfilter = vector<bool>(size_bf, false);
}
vector<long long> bloomfilterClass::hashFun(string pass) {

	int primes[7] = { 3, 5, 7, 11, 13, 17, 19 };
	vector<long long> finHash;
	for (int i = 0;i < 7;i++) { //7 hashes
		long long h = primes[i];
		for (char c : pass) {
			h = h* 131 + int(c); //not too simple hash to randomize better
		}
		if (h < 0)h = -h;
		finHash.push_back(h);
	}
	return finHash;
}
vector<long long>bloomfilterClass::hashIndex(vector<long long> hashcode) {
	vector<long long> finIndex;
	for (int i = 0;i < 7;i++) {
		finIndex.push_back(hashcode[i] % size_bf);
	}
	return finIndex;
}
void bloomfilterClass::insert(string pass) {
	vector<long long> finHash = hashFun(pass);
	vector<long long> finIndex = hashIndex(finHash);
	for (int i = 0;i < 7;i++) {
		bloomfilter[finIndex[i]] = true;
	}
}

void bloomfilterClass::readData(string filename) {
	string linefromfile;
	ifstream inFile(filename);
	while (getline(inFile, linefromfile)) {
		insert(linefromfile);
	}
}

pair<bool, int64_t> bloomfilterClass::search(string pass) {
	auto start = chrono::high_resolution_clock::now();
	vector<long long> inputHash = hashFun(pass);
	vector<long long> inputIndex = hashIndex(inputHash);
	bool present = true;
	for (int i = 0; i<7; i++) {
		if (!bloomfilter[(inputIndex[i])]) {
			present = false; //if any of the checked bits is false then the target is in the vector
			auto end = chrono::high_resolution_clock::now();
			auto time = duration_cast<chrono::nanoseconds>(end - start);
			return make_pair(present, time.count());
		}
	}
	auto end = chrono::high_resolution_clock::now();
	auto time = duration_cast<chrono::nanoseconds>(end - start);
	return make_pair(present, time.count());
}


