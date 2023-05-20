#include "token.h"

ostream& operator<<(ostream& os, const Token& t){
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
        case TokenType::PAREN_RIGHT:
            os << "PAREN_RIGHT";
            break;
        case TokenType::PAREN_LEFT:
            os << "PAREN_LEFT";
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
        case TokenType::EULER:
            os << "EULER";
            break;
        case TokenType::PI:
            os << "PI";
            break;
    }
    os << ": '" << t.value << "'}";
    return os;
}