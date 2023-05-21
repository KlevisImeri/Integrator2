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
   //constructor
   Lexer():str(""),tokenList(){}
   Lexer(string str):str(str),tokenList(){}
   //setters|getters
   void setString(const string& str){this->str=str;}
   string getStr(){return str;}
   vector<Token> getTokenList(){return tokenList;}
   //methods
   void askForFunction();
   void tokenize();
   void print(ostream& os) const;
   void operator=(const string& str);
};
//operator << overloading
ostream& operator<<(ostream& os, const Lexer& lexer);
#endif 