#ifndef parser_h
#define parser_h

#include "token.h"
#include "tree.h"
#include "menu.h"
#include <vector>
#include <stack>

using namespace std;

class Parser{
   Tree tree;
   vector<Token> output;
   public:
   Parser(vector<Token> tokens){parse(tokens);}
   vector<Token> shunting_yard(const vector<Token>& tokens);
   bool parse(vector<Token> tokens);
   Tree& getFunction() {return tree;}
   double integrate(MenuData limits);
};

#endif