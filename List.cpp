#include "List.h"

List::List() : head(nullptr), tail(nullptr), node_count(0) {}

bool List::isEmpty() const {
    return head == nullptr;
}

void List::push_front(const string& x) {
    Node* newNode = new Node(x);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    ++node_count;
}

Node* List::getNode(unsigned int index) const {
    if (index >= node_count) {
        return nullptr;
    }
    Node* current = head;
    unsigned int i = 0;
    while (current != nullptr && i < index) {
        current = current->next;
        ++i;
    }
    return current;
}

unsigned int List::getNodeCount() const {
    return node_count;
}

List::List(const List& rhs) : head(nullptr), tail(nullptr), node_count(0) {
    Node* current = rhs.head;
    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++node_count;
        current = current->next;
    }
}

List& List::operator=(const List& rhs) {
    if (this == &rhs) return *this;

    // clear existing
    Node* cur = head;
    while (cur != nullptr) {
        Node* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    head = tail = nullptr;
    node_count = 0;

    // copy from rhs
    Node* current = rhs.head;
    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++node_count;
        current = current->next;
    }
    return *this;
}

List::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* tmp = current->next;
        delete current;
        current = tmp;
    }
    head = tail = nullptr;
    node_count = 0;
}