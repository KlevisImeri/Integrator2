#ifndef node_h
#define node_h
#include <vector>

using namespace std;

template <typename T>
class Node{
 private:
    T data;
    vector<Node<T>*> children;
 public:
    Node(T data);
    void addChild(Node<T>* child);
    friend ostream& operator<<(ostream& os, const Node<T>& node);
};

ostream& operator<<(ostream& os, const Node<T>& node);

#endif