#include "node.h"

template <typename T>
Node<T>::Node(T data):data(data){}

template <typename T>
void Node<T>::addChild(Node<T>* child) {
    children.push_back(child);
}

template <typename T>
ostream& operator<<(ostream& os, const Node<T>& node){
    //you dont knwo the type of the data so you can't just
    //os<< everything. But for this project we are using tokens
    //therefore we wont chechk before we output.
    os<<data;
}

