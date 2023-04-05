#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

inline int charToInt(char c){
	return c-'0';
}

inline void clearInputBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF) { } 
}

Menu::Menu(){
     dx = 0.01; X_0 = -3.14; X_n=3.14;
}

void Menu::start(){
    do{
        system("clear");

        printf( "\ndx = %g    X_0 = %g    X_n = %g\n", dx, X_n, X_0);
        printf( "   0.Change dx.\n"
                "   1.Change X_0.\n"
                "   2.Change X_n.\n"
                "   3.Continue.\n");
        printf("Enter option: "); 
        input = getchar();
        clearInputBuffer();

        switch(charToInt(input)){
            case 0:
                printf("Enter partition: ");
                scanf("%lf", &dx);
                break;
            case 1:
                printf("Enter Lower bound: ");
                scanf("%lf", &X_0);
                break;
            case 2:
                printf("Enter Upper bound: ");
                scanf("%lf", &X_n);
                break;
            case 3:
                printf("Press Enter to continue...");
                break;
            default:
                printf("You entered invalid input!");
                break;
            }
            clearInputBuffer();            
        }while(charToInt(input) !=3);
    }

void Menu::print(){
    printf( "dx = %g    X_0 = %g    X_n = %g\n", dx, X_n, X_0);
}
