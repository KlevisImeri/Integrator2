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
    Node(Token data);
    Node(TokenType type, string str);

    //seters|geters
    void setData(Token data);
    Token getData();
    vector<Node*> getChildren();
    Node* getChildAtIndex(int i) const;

    //methods    
    int numberOfChildren() const;
    bool hasChildren() const;
    void addChild(Node& child);
    void print(bool lastone) const;

    //operator overloading
    friend ostream& operator<<(ostream& os, const Node& node);
};

ostream& operator<<(ostream& os, const Node& node);

#endif