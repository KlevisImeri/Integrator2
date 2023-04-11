#ifndef token_h
#define token_h

#include <string>
#include <iostream>

using namespace std;

enum class TokenType{
    NONE,
    NUMBER,
    OPERATOR,
    PARENTHESES,
    COMA,
    FUNCTION,
    VARIABLE
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