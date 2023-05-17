#ifndef rational_h
#define rational_h

#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

class Rational_{
    int numerator;
    int denominator;
    public:
    Rational_(int numerator, int denominator);
    Rational_(double x);
    int getNumerator() const {return numerator;}
    int getDenominator() const { return denominator;}
    friend ostream& operator<<(ostream& os, const Rational_& r);
    operator double();
};

ostream& operator<<(ostream& os, const Rational_& r);

#endif