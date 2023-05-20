#ifndef lexer_h
#define lexer_h
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "token.h"
#include "exceptions.h"
using namespace std;

class Lexer{
   string str;
   vector<Token> tokenList;
   void validArity(Token token, int pos);
   public:
   Lexer():str(""),tokenList(){}
   Lexer(string str):str(str),tokenList(){}
   // ~Lexer(){cout<<"Deleting Lexer"<<endl;}
   void askForFunction();
   void setString(const string& str){this->str=str;}
   void tokenize();
   string getStr(){return str;}
   vector<Token> getTokenList(){return tokenList;}
   void print() const;
};

#endif 