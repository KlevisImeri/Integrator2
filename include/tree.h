#ifndef tree_h
#define tree_h
#include <iostream>
#include "node.h"
#include "token.h"


class Tree{
 private:
   Node root;
 public:
   //constuctors
   Tree(Node node);
   Tree(TokenType type, string str);

   //setter|getters
   void setRoot(const Node& node);
   Node getRoot();
   

   //methods
   // void newNode(Node* parent, T data){
   //    parent
   // }
   void addChild(Node &child);
   void addChild(Node& parent, Node& child);
   void print(const Node& root, string prefix, bool lastone) const;
   //operator overloading
   friend std::ostream& operator<<(ostream& os, const Tree& tree);
};


ostream& operator<<(ostream& os, const Tree& tree);

#endif