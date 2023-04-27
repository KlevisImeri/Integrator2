#ifndef tree_h
#define tree_h
#include <iostream>
#include "node.h"
#include "token.h"


enum Treetype{
  NORMAL,
  BINARY,
  EXPRESSION,
};


class Tree{
 private:
   Treetype type;
   double xValue;
   Node root;
 public:
   //constuctors
   Tree();
   Tree(Node node);
  Tree(TokenType type, string str);
    
   //methods
   void buildExpressionTree(vector<Token> tokens);
   void NodeExpressionTree(Node& node, vector<Token>& tokens);
   double evaluate(double x);
   double Nodeeval(Node& node);
   void print(const Node& root, string prefix, bool lastone) const;

   //operator overloading
   friend std::ostream& operator<<(ostream& os, const Tree& tree);
};


ostream& operator<<(ostream& os, const Tree& tree);

#endif