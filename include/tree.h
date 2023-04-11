#ifndef tree_h
#define tree_h
#include "node.h"

template <typename T>
class Tree{
 private:
    Node<T>* root;
 public:
    //constuctor
    Tree();
    Tree(Node<T>* node);

    void setRoot(Node<T>* node);
    friend void addChild(Node<T>* parent, Node<T>* child);
    friend ostream& operator<<(ostream& os, const Tree<T>& tree);
};

 ostream& operator<<(ostream& os, const Tree<T>& tree)

#endif