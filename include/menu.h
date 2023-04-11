#ifndef menu_h
#define menu_h

class Menu{
 private:
    double dx;
    double X_0;
    double X_n;
    int input;
 public:
    Menu(double X_0=1, double X_n=1, double dx=0.01);
    void start();
    void print() const;
};

#endif
