#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "menu.h"
#include "lexer.h" 
#include "node.h"
#include "tree.h"
#include "token.h"
#include "parser.h"
#include "bmpimage.h"


using namespace std;
// menu→→integrator
// ↓                
// lexor → String   
// ↓                
// parser → shuting yard algo, expression tree
// ↓
// integrator → evaluator
// ↓
// Output

/*To do:
    3. write mutiple interface inheritance:
        printeble 

    6. write the documentation
*/
int main(){
    Menu menu(-3.14, 3.14, 0.01);
    try{
        menu.start();
    }catch(const exception& e){
        cerr<<e.what()<<endl;
        return -1;
    }
    Lexer lexer;
    lexer.askForFunction();
    cout<<lexer;
    Parser parser(lexer.getTokenList());
    cout<<fixed << setprecision(10)<<"Integral: "<<parser.integrate(menu.getData())<<endl;
    
    // parser.getFunction().evaluate(3);
    BmpImage image;
    image.backgroundcolor(); 
    image.resize(7);
    try{
        image.integral(parser.getFunction(), menu.getData());
    }catch(const exception &e){
        cerr<<e.what()<<endl;
    }
    image.plane();
    try{
        image.function(parser.getFunction());
    }catch(const exception &e){
        cerr<<e.what()<<endl;
    }
    image.create();

    return 0;
}




