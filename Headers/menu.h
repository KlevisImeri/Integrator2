#ifndef menu_h
#define menu_h


inline int charToInt(char c);
inline void clearInputBuffer();
class Menu{
private:
    double dx;
    double X_0;
    double X_n;
    char input;
public:
    Menu();
    void start();
    void print();
};

#endif
