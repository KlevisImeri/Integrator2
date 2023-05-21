#ifndef exceptions_h
#define exceptions_h

#include <iostream>
#include <string>
#include <exception>
using namespace std;

class InvalidDoubleInput: public exception{
    public:
    const char* what() const noexcept{
        return "Invalid floating point number input!";
    }
};

class InvalidStringInput : public exception {
    string str;
    string msg;
    public:
    InvalidStringInput(char c):str(1, c), msg("Invalid character: " + str) {}
    InvalidStringInput(const string& s):str(s), msg("Invalid character: " + str) {}
    const char* what() const noexcept {
        return msg.c_str();
    }
};


class RuntimeError: public exception{
    string str;
    public:
    RuntimeError(char str):str(1,str){}
    RuntimeError(const string& str):str(str){}
    const char* what() const noexcept{
        return str.c_str();
    }
};

class DivByZero: public exception{
    public:
    const char* what() const noexcept{
        return "Division by zero is not allowed!";
    }
};

#endif