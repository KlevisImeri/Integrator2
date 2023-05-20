#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "menu.h"
#include "lexer.h" 
#include "tree.h"
#include "token.h"
#include "node.h"
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
    2. write the evaluator (integrtor)
    3. Error handling in lexer parser and evaluator 
    3. write mutiple interface inheritance
    4. write a class caled integrator
    5. build a struct for menu input
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
    lexer.print();
    Parser parser(lexer.getTokenList());
    cout<<fixed << setprecision(10)<<"Integral: "<<parser.integrate(menu.getData())<<endl;
    // parser.getFunction().evaluate(3);
    BmpImage image;
    image.backgroundcolor({24,25,26});
    image.resize(7);
    image.integral(parser.getFunction(), menu.getData());
    image.plane();
    image.function(parser.getFunction());
    image.create();
    


    return 0;

}




