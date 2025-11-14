#include "List.h"
#include <iostream>

//single linked list based on Module 3 Single Linked List Video and Programming 2 Project 1 code
using namespace std;

bool List::isEmpty() {
    return head == nullptr;
}

void List::push_front(const string& x) {
    Node *newNode = new Node(x);
    if (isEmpty())
        head = tail = newNode;
    else {
        newNode -> next = head;
        head = newNode;
    }
    node_count++;
}

Node* List::getNode(unsigned int index)
{
    Node* newnode;
    if (index >= node_count)
    {
        throw out_of_range("Out of Range");
    }
    newnode = head;
    for (unsigned int i=0 ; i < index; i++)
        newnode = newnode->next;
    return newnode;
}

unsigned int List::getNodeCount() {
    return node_count;
}

List::List(const List& rhs) //copy constructor
{
    node_count = 0;
    head = nullptr;
    tail = nullptr;

    Node* currentnode = rhs.head;
    while(currentnode != nullptr)
    {
        push_front(currentnode->data);
        currentnode=currentnode->next;
    }
}


List& List::operator=(const List& rhs){ //assignment operator
    Node* currentnode = head;
    while(currentnode!=nullptr)
    {
        Node* tempnode = currentnode->next;
        delete currentnode;
        currentnode = tempnode;
    }
    head = tail = nullptr;

    node_count = 0;
    Node* newnode = rhs.head;
    while(newnode != nullptr)
    {
        push_front(newnode->data);
        newnode=newnode->next;
    }

    return *this;
}

List::~List() { //destructor
    Node* currentnode = head;
    while (currentnode != nullptr) {
        Node* tempnode = currentnode-> next;
        delete currentnode;
        currentnode = tempnode;
    }
    head = tail = nullptr;
    node_count = 0;
}

