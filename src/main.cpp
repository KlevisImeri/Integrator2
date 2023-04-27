#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "string.h" 
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
    1. make the nodes dynamically allocated in the heap
    2. write the parser:
        1. shuntung yard
        2. expression tree
    3. write the evaluator (integrtor)
    4. write image creator (inheritance file?)
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
    image.verticalLine(0,{255,255,255});
    image.verticalLine(1,{255,255,255},0.1);
    image.verticalLine(-1,{255,255,255},0.1);
    image.horizontalLine(0,{255,255,255});
    image.function(parser.getTree(), {225,225,225});
    image.create();
    

    return 0;

}




