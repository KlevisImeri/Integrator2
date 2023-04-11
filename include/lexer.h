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
    int Tsize;
    Token *pT;
 public:
    Lexer();
    Lexer(string strin);
    Lexer(const Lexer& lexer);
    ~Lexer();
    void askForFunction();
    void setString(const string& strin);
    bool tokenize();
    bool isFunctionValid();
    Token* getTokenList();
    void print() const;
};

#endif 