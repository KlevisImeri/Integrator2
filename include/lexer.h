#ifndef lexer_h
#define lexer_h
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "token.h"

class Lexer{
 private:
    string str;
    vector<Token> tokenList;
 public:
    Lexer();
    Lexer(string strin);
    Lexer(const Lexer& lexer);
    void askForFunction();
    void setString(const string& strin);
    bool tokenize();
    bool tokenizeValid();
    vector<Token> getTokenList();
    void print() const;
};

#endif 