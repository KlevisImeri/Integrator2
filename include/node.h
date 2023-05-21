#ifndef node_h
#define node_h
#include <iostream>
#include <vector>
#include "token.h"
using namespace std;

template<class T>
class Node{
    T data;
    vector<Node<T>*> children;
    public:
    //constructors
    Node(){}
    Node(T data):data(data),children(vector<Node*>(0)){}
    //destructor
    ~Node();
    //seters|geters
    void setData(T data){this->data = data;}
    T getData(){return data;}
    vector<Node*> getChildren(){return children;}
    Node* getChildAtIndex(int i) const {return children[i];}
    //methods    
    int numberOfChildren() const{return children.size();}
    bool hasChildren() const{return children.size()!=0;}
    void addChild(T data);
    void print(ostream& os, bool lastone) const;
    //friends
    friend class Tree;
};
//destructor
template<class T>
Node<T>::~Node(){
    //cout<<data<<endl;
    if(children.empty()) return;
    for(auto i : children){
        if(i==NULL) return;
        delete i;
    }
    children.clear();
}

//methods
template<class T>
void Node<T>::addChild(T data){
    Node* child = new Node<Token>(data);
    children.push_back(child);
}

template<class T>
void Node<T>::print(ostream& os, bool lastone) const{
    if(lastone){
        os<<"└──"<<data;  
    }else{
        os<<"├──"<<data;
    }    
}

//operator overloading
template<class T>   
ostream& operator<<(ostream& os, const Node<T>& node){
    node.print(os,false);
    return os;
}

//operator << overloading
template<class T>
ostream& operator<<(ostream& os, const Node<T>& node);

#endif