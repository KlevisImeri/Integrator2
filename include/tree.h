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
  Node<Token> root;
  public:
  //constuctors
  Tree():root(),type(NORMAL){}
  Tree(Node<Token> node):root(node),type(NORMAL){}
Tree(TokenType type, string str):root({type,str}),type(NORMAL){}
  //methods
  void buildExpressionTree(vector<Token>& tokens, Node<Token>* node=NULL);
  double evaluate(double x, Node<Token>* node = NULL);
  void print(ostream& os, const Node<Token>& root, string prefix, bool lastone) const;

  //operator << overloading
  friend ostream& operator<<(ostream& os, const Tree& tree);
};

//operator << overloading
ostream& operator<<(ostream& os, const Tree& tree);

#endif