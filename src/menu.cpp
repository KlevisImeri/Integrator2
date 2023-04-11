#include <iostream>
// #include <cstdlib>
#include "menu.h"

using namespace std;

Menu::Menu(double X_0, double X_n, double dx){
     this->dx= dx; 
     this->X_0= X_0; 
     this->X_n= X_n;
     input= 0;
}

void Menu::start(){
    do{
        system("clear");

        cout<<"dx = "<<dx<<"  X_0 ="<<X_0<<"  X_n = "<<X_n<<endl;
        cout<<"   1.Change dx."     <<endl;
        cout<<"   2.Change X_0."    <<endl;
        cout<<"   3.Change X_n."    <<endl;
        cout<<"   9.Continue."      <<endl;
        cout<<"Enter option: ";
        cin >> input;

        switch(input){
            case 1:
                cout<<"Enter partition: ";
                cin>>dx;
                break;
            case 2:
                cout<<"Enter Lower bound: ";
                cin>>X_0;
                break;
            case 3:
                cout<<"Enter Upper bound: ";
                cin>>X_n;
                break;
            }          
    }while(input!=9);
}

void Menu::print() const{
    cout<<"dx = "<<dx<<"   X_0 = "<<X_n<<"    X_n = "<<X_0<<endl;
}
