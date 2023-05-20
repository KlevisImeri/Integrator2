#ifndef tree_h
#define tree_h
#include <iostream>
#include <cmath>
#include "rational.h"
#include "node.h"
#include "token.h"
#include "exceptions.h"
using namespace std;


enum Treetype{
  NORMAL,
  BINARY,
  EXPRESSION,
};


class Tree{
  Treetype type;
  Node root;
  public:
  //constuctors
  Tree():root(),type(NORMAL){}
  Tree(Node node):root(node),type(NORMAL){}
  Tree(TokenType type, string str):root(type,str),type(NORMAL){}
  // ~Tree(){cout<<"deleting Tree"<<endl;}
  //methods
  void buildExpressionTree(vector<Token>& tokens, Node* node=NULL);
  double evaluate(double x, Node* node = NULL);
   
  void print(ostream& os, const Node& root, string prefix, bool lastone) const;

  //operator overloading
  friend std::ostream& operator<<(ostream& os, const Tree& tree);
};


ostream& operator<<(ostream& os, const Tree& tree);

#endif