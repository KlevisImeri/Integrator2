#include "rational.h"

Rational_::Rational_(int numerator, int denominator){
    int gcd = __gcd(numerator, denominator);
    this->numerator = numerator / gcd;
    this->denominator = denominator / gcd;
}
Rational_::Rational_(double x) {
    double tolerance = 0.00001;
    int max_iterations = 8;
    int i = 0;
    while (abs(x - round(x)) > tolerance && i < max_iterations) {
        x *= 10;
        i++;
    }
    cout<<x<<'/'<<pow(10, i)<<endl;
    numerator = (int)(round(x));
    denominator = pow(10, i);

    int gcd = __gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}
Rational_::operator double(){
    return (double)numerator/denominator;
}

ostream& operator<<(ostream& os, const Rational_& r){
    os<<r.numerator<<'/'<<r.denominator;
    return os;
}