#ifndef node_h
#define node_h
#include <iostream>
#include <vector>
#include "token.h"

using namespace std;

class Node{
 private:
    Token data;
    vector<Node*> children;
 public:
    //constructors
    Node();
    Node(Token data);
    Node(TokenType type, string str);
    //destructor
    ~Node();

    //seters|geters
    void setData(Token data);
    Token getData();
    vector<Node*> getChildren();
    Node* getChildAtIndex(int i) const;

    //methods    
    int numberOfChildren() const;
    bool hasChildren() const;
    void addChild(Token token);
    void print(bool lastone) const;

    //operator overloading
    friend ostream& operator<<(ostream& os, const Node& node);
    friend class Tree;
};

ostream& operator<<(ostream& os, const Node& node);

#endif