#include "menu.h"

bool Menu::isValidDouble(const string str) const{
    if (str.empty()) return false;

    bool hasDecimalPoint = false;
    bool hasDigit = false;

    for (int i = 0; i < str.size(); i++) {
        if (i == 0 && (str[i] == '-' || str[i] == '+')) {
            continue;  // Skip the sign character if it's the first character
        } else if (str[i] == '.') {
            if (hasDecimalPoint) {
                return false;  // Multiple decimal points are not allowed
            }
            hasDecimalPoint = true;
        } else if ('0' <= str[i] && str[i] <= '9') {
            hasDigit = true;
        } else {
            return false;  // Invalid character
        }
    }

    return hasDigit;
}

void Menu::waitEnter() const{
    cout<<"Press enter to continue!";
    char n;
    do{
        cin.ignore();
        cin.get(n);
    }while(n!='\n');
}

Menu::Menu(double X_0, double X_n, double dx){
     this->dx=to_string(dx);
     this->X_0=to_string(X_0); 
     this->X_n=to_string(X_n);
     input='\0';
}

void Menu::start(){
    do{
        system("clear"); //may depend on the system

        cout<<"dx = "<<dx<<"  X_0 ="<<X_0<<"  X_n = "<<X_n<<endl;
        cout<<"   1.Change dx."     <<endl;
        cout<<"   2.Change X_0."    <<endl;
        cout<<"   3.Change X_n."    <<endl;
        cout<<"   9.Continue."      <<endl;
        cout<<"Enter option: ";
        cin >> input;

        string x;
        switch(input){
            case '1':
                cout<<"Enter partition: ";
                cin>>x;
                if(isValidDouble(x)){
                    dx=x;
                }else{
                    cout<<"Please enter a valid float pointing number!"<<endl;
                    waitEnter();
                }
                break;
            case '2':
                cout<<"Enter Lower bound: ";
                cin>>x;
                if(isValidDouble(x)){
                    X_0=x;
                }else{
                    cout<<"Please enter a valid float pointing number!"<<endl;
                    waitEnter();
                }
                break;
            case '3':
                cout<<"Enter Upper bound: ";
                cin>>x;
                if(isValidDouble(x)){
                    X_n=x;
                }else{
                    cout<<"Please enter a valid float pointing number!"<<endl;
                    waitEnter();
                }
                break;
            }          
    }while(input!='9');

    //if one of the inputs is not double
    if(!isValidDouble(dx) || !isValidDouble(X_0) || !isValidDouble(X_n)) throw InvalidDoubleInput();
}

void Menu::print() const{
    cout<<"dx = "<<dx<<"   X_0 = "<<X_n<<"    X_n = "<<X_0<<endl;
}
