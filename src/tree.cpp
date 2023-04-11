#include "tree.h"

template <typename T>
Tree<T>::Tree():root(NULL){}

template <typename T>
Tree<T>::Tree(Node<T>* node):root(node){}

template <typename T>
void Tree::setRoot(Node<T>* node){
    root = node;
}

template <typename T>
void Tree::addChild(Node<T>* parent, Node<T>* child){
    parent->addChild(child);
}

template <typename T>
ostream& operator<<(ostream& os, const Tree<T>& tree){
    if
}