#ifndef LIST_H
#define LIST_H

#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
    explicit Node(const string& d) : data(d), next(nullptr) {}
};

class List {
private:
    Node* head;
    Node* tail;
    unsigned int node_count;

public:
    List();
    List(const List& rhs);
    List& operator=(const List& rhs);
    ~List();

    bool isEmpty() const;
    void push_front(const string& x);
    Node* getNode(unsigned int index) const;
    unsigned int getNodeCount() const;
};

#endif
