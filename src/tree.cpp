#include "tree.h"
#include <cmath>
//constuctors
Tree::Tree(){}
Tree::Tree(Node node):root(node),type(NORMAL),xValue(0){}
Tree::Tree(TokenType type, string str):root(type,str),type(NORMAL),xValue(0){}

//methods
void Tree::print(const Node& node, string prefix, bool lastone) const{
    cout<< prefix;
    if(lastone){
        node.print(true);
    }else{
        node.print(false);
    }
    cout<<endl;
    if(node.hasChildren()){
        int size = node.numberOfChildren();
        for(int i = 0; i<size; i++){
            if(i+1==size){
                Tree::print(*(node.getChildAtIndex(i)),prefix+"     ",true);
            }else{
                Tree::print(*(node.getChildAtIndex(i)),prefix+"     ",false);
            }
            
        }
    }
};

void Tree::buildExpressionTree(vector<Token> tokens){
    type = EXPRESSION;
    if (tokens.empty()) {return;}
    root.data = tokens.back();
    tokens.pop_back();
    
    int numchildren = 0;
    if(root.data.type == TokenType::FUNCTION){
        numchildren = FUNCTION_ARITY.at(root.data.value);
    }else if(root.data.type == TokenType::OPERATOR){
        numchildren = 2;
    }else{
        return;
    }
    for(int i = 0; i<numchildren; i++){
        if (tokens.empty()) {return;}
        root.addChild(tokens.back());
        tokens.pop_back();
        NodeExpressionTree(*(root.children[i]),tokens);
    }
}

void Tree::NodeExpressionTree(Node& node, vector<Token>& tokens){
    //cout<<node.data<<": ";
    if(tokens.empty()){ return;}
    int numchildren = 0;
    if(node.data.type == TokenType::FUNCTION){
        numchildren = FUNCTION_ARITY.at(node.data.value);
    }else if(node.data.type == TokenType::OPERATOR){
        numchildren = 2;
    }else{
        return;
    }
    for(int i = 0; i<numchildren; i++){
        if (tokens.empty()) {return;}
        node.addChild(tokens.back());
        tokens.pop_back();
       //cout<<*(node.children[i])<<endl;
        NodeExpressionTree(*(node.children[i]),tokens);
    }
}
double Tree::evaluate(double x){
    //cout<<"eval function\n";
    if(type!=EXPRESSION){
        cout<<"You can not evaluate a non expression tree!"<<endl;
        return 0;
    };
    xValue = x;
    string value = root.data.value;
    switch (root.data.type) {
        case TokenType::NUMBER:
        //cout<<"number"<<endl;
            return stod(value);
            break;
        case TokenType::OPERATOR:
            //cout<<"operator"<<endl;
            switch (value[0]){
                case '+':
                    return Nodeeval(*root.children[1])+Nodeeval(*root.children[0]);
                    break;
                case '-':
                    return Nodeeval(*root.children[1])-Nodeeval(*root.children[0]);
                    break;
                case '*':
                    //cout<<Nodeeval(*root.children[1])<<'*'<<Nodeeval(*root.children[0])<<endl;
                    return Nodeeval(*root.children[1])*Nodeeval(*root.children[0]);
                    break;
                case '/':
                    return Nodeeval(*root.children[1])/Nodeeval(*root.children[0]);
                    break;
                case '^':
                    return pow(Nodeeval(*root.children[1]),Nodeeval(*root.children[0]));
                    break;
                default:
                    break;
            }
            break;
        case TokenType::FUNCTION:
            //cout<<"function"<<endl;
            if(value=="sin"){
                return sin(Nodeeval(*root.children[0]));
            }else if(value=="cos"){
                return cos(Nodeeval(*root.children[0]));
            }else if(value=="log"){
              return log(Nodeeval(*root.children[0]))/log(Nodeeval(*root.children[1]));
            }else{
              //fucntion type does not exits
              return 0;
            }
            break;
        case TokenType::VARIABLE:
            //cout<<"Variable"<<endl;
            return xValue;
            break;
        case TokenType::EULER:
            //cout<<"Euler"<<endl;
            return 2.71828;
            break;
        case TokenType::PI:
            //pcout<<"PI"<<endl;
            return 3.14159265359;
            break;
        default:
            // Handle unknown token type
            return 0;
            break;
    }
}   
double Tree::Nodeeval(Node& node){
    string value = node.data.value;
        switch (node.data.type) {
            case TokenType::NUMBER:
                return stod(value);
                break;
            case TokenType::OPERATOR:
                switch (value[0]){
                    case '+':
                        return Nodeeval(*node.children[1])+Nodeeval(*node.children[0]);
                        break;
                    case '-':
                        return Nodeeval(*node.children[1])-Nodeeval(*node.children[0]);
                        break;
                    case '*':
                        return Nodeeval(*node.children[1])*Nodeeval(*node.children[0]);
                        break;
                    case '/':
                        //cout<<*node.children[1]<<'/'<<*node.children[0];   
                        //cout<<"="<<Nodeeval(*node.children[1])/Nodeeval(*node.children[0])<<endl;
                        return Nodeeval(*node.children[1])/Nodeeval(*node.children[0]);
                        break;
                    case '^':
                        return pow(Nodeeval(*node.children[1]),Nodeeval(*node.children[0]));
                        break;
                    default:
                        //return operator doesnt exits
                        return 0;
                        break;
                }
                break;
            case TokenType::FUNCTION:
                if(value=="sin"){
                    return sin(Nodeeval(*node.children[0]));
                }else if(value=="cos"){
                    return cos(Nodeeval(*node.children[0]));
                }else if(value=="log"){
                    return log(Nodeeval(*node.children[0]))/log(Nodeeval(*node.children[1]));
                }else{
                  //fucntion type does not exits 
                  return 0;
                }
                break;
            case TokenType::VARIABLE:
                return xValue;
                break;
            case TokenType::EULER:
                return 2.71828;
                break;
            case TokenType::PI:
                return 3.14159265359;
                break;
            default:
                // Handle unknown token type
                return 0;
                break;
        }
}

//operator overloading
ostream& operator<<(ostream& os, const Tree& tree){
    tree.print(tree.root,"",true);
    return os;  
}