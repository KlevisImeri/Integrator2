#ifndef token_h
#define token_h

#include <string>
#include <iostream>
#include <stack>
#include <queue>
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

enum class TokenType{
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

    Token(): type(TokenType::NONE), value(""){}
    Token(TokenType type, string value) : type(type), value(value){}
    friend std::ostream& operator<<(std::ostream& os, const Token& t);
};

std::ostream& operator<<(std::ostream& os, const Token& t);

#endif 