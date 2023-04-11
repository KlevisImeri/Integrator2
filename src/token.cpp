#include "token.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Token& t){
    os << "{";
    switch(t.type) {
        case TokenType::NONE:
            os << "NONE";
            break;
        case TokenType::NUMBER:
            os << "NUMBER";
            break;
        case TokenType::OPERATOR:
            os << "OPERATOR";
            break;
        case TokenType::PARENTHESES:
            os << "PARENTHESES";
            break;
        case TokenType::COMA:
            os << "COMA";
            break;
        case TokenType::FUNCTION:
            os << "FUNCTION";
            break;
        case TokenType::VARIABLE:
            os << "VARIABLE";
            break;
    }
    os << ": '" << t.value << "'}";
    return os;
}