#ifndef token_h
#define token_h

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Define operator precedence
const unordered_map<char, int> PRECEDENCE{
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
};

// Define supported functions and their arities
const unordered_map<string, int> FUNCTION_ARITY{
    {"sin", 1},
    {"cos", 1},
    {"tan", 1},
    {"log", 2},
};

// Token Types
enum TokenType{
    NONE,
    NUMBER,
    OPERATOR,
    PAREN_RIGHT,
    PAREN_LEFT,
    COMA,
    FUNCTION,
    VARIABLE,
    EULER,
    PI
};

class Token{
public:
    TokenType type;
    string value;
    //contructors
    Token():type(NONE),value(""){}
    Token(TokenType type, char value):type(type),value(1, value){}
    Token(TokenType type, string value):type(type),value(value){}
    //oprator <<
    friend ostream& operator<<(ostream& os, const Token& t);
};

ostream& operator<<(ostream& os, const Token& t);

#endif 