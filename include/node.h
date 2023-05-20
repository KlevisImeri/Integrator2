#ifndef node_h
#define node_h
#include <iostream>
#include <vector>
#include "token.h"

using namespace std;

class Node{
    Token data;
    vector<Node*> children;
 public:
    //constructors
    Node(){}
    Node(Token data):data(data),children(vector<Node*>(0)){}
    Node(TokenType type, string str):data(type,str){}
    //destructor
    ~Node();
    //seters|geters
    void setData(Token data){this->data = data;}
    Token getData(){return data;}
    vector<Node*> getChildren(){return children;}
    Node* getChildAtIndex(int i) const {return children[i];}

    //methods    
    int numberOfChildren() const{return children.size();}
    bool hasChildren() const{return children.size()!=0;}
    void addChild(Token token);
    void print(ostream& os, bool lastone) const;

    //operator overloading
    friend ostream& operator<<(ostream& os, const Node& node);
    friend class Tree;
};

ostream& operator<<(ostream& os, const Node& node);

#endif