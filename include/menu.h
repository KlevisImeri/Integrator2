#ifndef menu_h
#define menu_h

#include <iostream>
#include <string>
#include "exceptions.h"
using namespace std;

struct MenuData{
  double dx;
  double X_0;
  double X_n;
};

class Menu{
  string dx;
  string X_0;
  string X_n;
  char input;
  bool isValidDouble(const string str) const;
  void waitEnter() const;
  public:
  Menu(double X_0=1, double X_n=1, double dx=0.01);
  double getStart() const {return stod(X_0);}
  double getEnd()const {return stod(X_n);}
  double getSize()const {return stod(dx);}
  MenuData getData() const {return {stod(dx),stod(X_0),stod(X_n)};};
  void start();
  void print() const;
};

#endif
