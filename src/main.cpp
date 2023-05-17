#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "lexer.h" 
#include "tree.h"
#include "token.h"
#include "node.h"
#include "parser.h"
#include "bmpimage.h"
#include <cmath>


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
    1. make shure the nodes are deleted if allocated dynamically (chechk it through class objt counter)
    2. write the evaluator (integrtor)
    3. Error handling in lexer parser and evaluator
    3. write mutiple interface inheritance
    4. write a class caled integrator
    5. build a struct for menu input
    6. write the documentation

*/
int main(){
    Menu menu(-3.14, 3.14, 0.01);
    menu.start();
    Lexer lexer;
    Parser parser;
    lexer.askForFunction();
    lexer.tokenize();
    lexer.print();
    parser.parse(lexer.getTokenList());
    

    BmpImage image;
    image.backgroundcolor({24,25,26});
    image.resize(7);
    image.integral(parser.getFunction(), menu.getStart(), menu.getEnd(), menu.getSize());
    image.plane();
    image.function(parser.getFunction());
    cout<<"hello"<<endl;
    image.create();

    return 0;

}




