#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "string.h" 
#include "lexer.h" 

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

int main(){
    Menu menu(-3.14, 3.14, 0.01);
    menu.start();
    Lexer lexer;
    lexer.askForFunction();
    lexer.tokenize();
    lexer.print();
    return 0;
}

// #include <stack>
// #include <queue>
// #include <unordered_map>

// // Define operator precedence
// const std::unordered_map<char, int> PRECEDENCE{
//     {'+', 1},
//     {'-', 1},
//     {'*', 2},
//     {'/', 2},
//     {'^', 3},
// };

// #include <stack>
// #include <queue>
// #include <unordered_map>
// #include <unordered_set>

// // Define operator precedence
// const std::unordered_map<char, int> PRECEDENCE{
//     {'+', 1},
//     {'-', 1},
//     {'*', 2},
//     {'/', 2},
//     {'^', 3},
// };

// // Define supported functions and their arities
// const std::unordered_map<std::string, int> FUNCTION_ARITY{
//     {"sin", 1},
//     {"cos", 1},
//     {"tan", 1},
//     {"log", 2},
// };

// // Shunting yard algorithm
// std::queue<Token> shunting_yard(const std::vector<Token>& tokens) {
//     queue<Token> output; // Output queue
//     stack<Token> op_stack; // Operator stack

//     for (const Token& token : tokens) {
//         if (token.type == TokenType::NUMBER || token.type == TokenType::VARIABLE) {
//             // If the token is a number or a variable, enqueue it
//             output.push(token);
//         } else if (token.type == TokenType::OPERATOR) {
//             // If the token is an operator, pop operators from the stack to the output queue
//             // until the stack is empty or the top operator has lower precedence than the token
//             while (!op_stack.empty() && op_stack.top().type == TokenType::OPERATOR
//                    && PRECEDENCE[token.value[0]] <= PRECEDENCE[op_stack.top().value[0]]) {
//                 output.push(op_stack.top());
//                 op_stack.pop();
//             }
//             // Push the operator onto the stack
//             op_stack.push(token);
//         } else if (token.type == TokenType::FUNCTION) {
//             // If the token is a function, push it onto the stack
//             op_stack.push(token);
//         } else if (token.type == TokenType::PAREN_OPEN) {
//             // If the token is a left parenthesis, push it onto the stack
//             op_stack.push(token);
//         } else if (token.type == TokenType::PAREN_CLOSE) {
//             // If the token is a right parenthesis, pop operators from the stack to the output queue
//             // until a left parenthesis or a function is found, which is then discarded
//             while (!op_stack.empty() && op_stack.top().type != TokenType::PAREN_OPEN
//                    && op_stack.top().type != TokenType::FUNCTION) {
//                 output.push(op_stack.top());
//                 op_stack.pop();
//             }
//             if (!op_stack.empty() && op_stack.top().type == TokenType::FUNCTION) {
//                 // Pop the function from the stack and enqueue it
//                 output.push(op_stack.top());
//                 op_stack.pop();
//             }
//             if (!op_stack.empty() && op_stack.top().type == TokenType::PAREN_OPEN) {
//                 op_stack.pop(); // Discard the left parenthesis
//             } else {
//                 throw std::runtime_error("Mismatched parentheses");
//             }
//         }
//     }
//     // Pop any remaining operators or functions from the stack to the output queue
//     while (!op_stack.empty()) {
//         if (op_stack.top().type == TokenType::PAREN_OPEN || op_stack.top().type == TokenType::PAREN_CLOSE) {
//             throw std::runtime_error("Mismatched parentheses");
//         }
//         output.push(op_stack.top());
//         op_stack.pop();
//     }
//     return output;
// }
