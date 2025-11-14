#include <string>
using namespace std;
struct Node {
    string data;
    Node *next;
    Node(const string& d) : data(d), next(nullptr) {}
};
class List {
    private:
        Node *head;
        Node *tail;
        unsigned int node_count;
    public:
        List(): head(nullptr), tail(nullptr), node_count(0) {}
        bool isEmpty();
        void push_front(const string& x);
        Node* getNode(unsigned int index);
        unsigned int getNodeCount();
        List(const List& rhs);
        List& operator=(const List& rhs);
        ~List();
    };


