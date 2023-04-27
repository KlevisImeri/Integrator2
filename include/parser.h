#ifndef parser_h
#define parser_h

#include "token.h"
#include "tree.h"
#include <vector>

using namespace std;

class Parser{
 private:
    Tree tree;
    vector<Token> output;
 public:
    Tree& getTree(){return tree;}
    vector<Token> shunting_yard(const vector<Token>& tokens);
    bool parse(vector<Token> tokens);
};

#endif