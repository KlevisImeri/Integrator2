#include "parser.h"

// Shunting yard algorithm
vector<Token> Parser::shunting_yard(const vector<Token>& tokens){
    stack<Token> op_stack; // Operator stack
    int numberFunctions = 0;
    for (const Token& token : tokens) {
        if (token.type == TokenType::NUMBER || token.type == TokenType::VARIABLE || token.type == TokenType::EULER || token.type == TokenType::PI) {
            // If the token is a number or a variable, enqueue it
            output.push_back(token);
        } else if (token.type == TokenType::OPERATOR) {
            // If the token is an operator, pop operators from the stack to the output queue
            // until the stack is empty or the top operator has lower precedence than the token
            while (!op_stack.empty() && ((op_stack.top().type == TokenType::OPERATOR && PRECEDENCE.at(token.value[0]) <= PRECEDENCE.at(op_stack.top().value[0]))||op_stack.top().type == TokenType::FUNCTION)){
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            // Push the operator onto the stack
            op_stack.push(token);
        } else if (token.type == TokenType::FUNCTION) {
            // If the token is a function, push it onto the stack
            op_stack.push(token);
            numberFunctions++;
        } else if (token.type == TokenType::PAREN_LEFT) {
            // If the token is a left parenthesis, push it onto the stack
            op_stack.push(token);
        } else if (token.type == TokenType::PAREN_RIGHT || token.type == TokenType::COMA) {
            // If the token is a right parenthesis, pop operators from the stack to the output queue
            // until a left parenthesis or a function is found, which is then discarded
            while (!op_stack.empty() && op_stack.top().type != TokenType::PAREN_LEFT && op_stack.top().type != TokenType::FUNCTION) {
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            if (!op_stack.empty() && op_stack.top().type == TokenType::FUNCTION) {
                // Pop the function from the stack and enqueue it
                output.push_back(op_stack.top());
                op_stack.pop();
                // while (!op_stack.empty() && op_stack.top().type != TokenType::PAREN_LEFT){}
                // op_stack.pop();
            }else if(!op_stack.empty() && op_stack.top().type == TokenType::PAREN_LEFT) {
                op_stack.pop(); // Discard the left parenthesis
            }else{
                throw RuntimeError("Mismatched parentheses");
            }
        }
        // //To print the operator stack
        // cout << "Operator stack: ";
        //     stack<Token> temp_stack = op_stack;
        //     while (!temp_stack.empty()) {
        //         cout << temp_stack.top().value << " ";
        //         temp_stack.pop();
        //     }
        // cout <<endl;
        //To print the output ouput
        // for(auto i: output){
        //     cout<<i;
        // }
        // cout<<endl;
    }
    
    // Pop any remaining operators or functions from the stack to the output queue
    while (!op_stack.empty()) {
        if (op_stack.top().type == TokenType::PAREN_RIGHT || op_stack.top().type == TokenType::PAREN_LEFT) {
            if(numberFunctions == 0){
                throw RuntimeError("Mismatched parentheses");
            }else{ 
                numberFunctions--;
            }
            op_stack.pop();
        }
        output.push_back(op_stack.top());
        op_stack.pop();
    }
    return output;
}

bool Parser::parse(vector<Token> tokens){
    // Reverse polish notation
    shunting_yard(tokens);
    
    // Printing the Output
    for(auto i : output){
        cout<<i<<endl;
    }
    
    // Building tree
    vector<Token> temp = output;
    tree.buildExpressionTree(temp);

    cout<<tree;

    return false;
}

double Parser::integrate(MenuData limits){
    double sum=0;
    for(double x=limits.X_0; x<=limits.X_n; x+=limits.dx){
        sum+=tree.evaluate(x)*limits.dx;
    }
    return sum;
}
