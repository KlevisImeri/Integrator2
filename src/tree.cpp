#include "tree.h"

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
bool Tree::odd(int x){
    return (x)%2==1;
}
double Tree::evaluate(double x){
    //cout<<root<<endl;
    if(type!=EXPRESSION){
        cout<<"You can not evaluate a non expression tree!"<<endl;
        return 0;
    };
    xValue = x;
    string value = root.data.value;
    double left, right, base;
    switch (root.data.type) {
        case TokenType::NUMBER:
        //cout<<"number"<<endl;
            return stod(value);
            break;
        case TokenType::OPERATOR:
            //cout<<"operator"<<value[0]<<endl;
            switch (value[0]){
                case '+':
                    if(root.children[1]==NULL){
                        return 0+Nodeeval(*root.children[0]);
                    }
                    return Nodeeval(*root.children[1])+Nodeeval(*root.children[0]);
                    break;
                case '-':
                    if(root.children[1]==NULL){
                        return 0-Nodeeval(*root.children[0]);
                    }
                    //cout<<Nodeeval(*root.children[1])<<'-'<<Nodeeval(*root.children[0])<<'\t';
                    return Nodeeval(*root.children[1])-Nodeeval(*root.children[0]);
                    break;
                case '*':
                    //cout<<Nodeeval(*root.children[1])<<'*'<<Nodeeval(*root.children[0])<<endl;
                    return Nodeeval(*root.children[1])*Nodeeval(*root.children[0]);
                    break;
                case '/':
                    left  = Nodeeval(*root.children[1]);
                    right = Nodeeval(*root.children[0]);
                    //cout<<left<<'/'<<right<<endl;
                    if(right>-0.0000001 && right<0.0000001){
                        cout<<"You can not divide by 0! Make shure you Interval is right!"<<endl;
                        return 0;
                    }
                    return left/right;
                    break;
                case '^':
                    if(root.children[0]->data.value=="/"){//special case when you have a division
                        left = Nodeeval(*(root.children[0]->children[1])); //numerator
                        right = Nodeeval(*(root.children[0]->children[0])); //denominator
                        base = Nodeeval(*root.children[1]); //base of the pewer
                        //cout<<base<<"^("<<left<<'/'<<right<<')'<<endl;
                        if(base>-0.0000001 && base<0.0000001) return 0;
                        if(base<0){//for negative x values
                            int gcd = __gcd((int)left,(int)right);
                            left/=gcd; right/=gcd;
                            if(odd(right)){ //if denominator is odd
                                if(odd(left)){
                                    return -pow(abs(base),left/right); //if left is odd you invert
                                }else{
                                return pow(abs(base),left/right); //if left is even you dont have to invert
                                }
                            }
                            return NAN;
                        }
                    }
                    left = Nodeeval(*root.children[0]);
                    base = Nodeeval(*root.children[1]);
                    cout<<base<<'^'<<left<<endl;
                    if(base>-0.0000001 && base<0.0000001) return 0; //its to close to 0 the power fucntion just can not compute
                    return pow(base,left); //positive x;
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
                double left=Nodeeval(*root.children[0]);
                if(left==1){
                    return 0;
                }
              return log(Nodeeval(*root.children[1]))/log(left);
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
            //cout<<"PI"<<endl;
            return 3.14159265359;
            break;
        default:
            // Handle unknown token type
            return 0;
            break;
    }
    return 0;
}   
double Tree::Nodeeval(Node& node){
    //cout<<node<<endl;
    string value = node.data.value;
    double left, right, base;
        switch (node.data.type) {
            case TokenType::NUMBER:
                //cout<<"number"<<endl;
                return stod(value);
                break;
            case TokenType::OPERATOR:
            //cout<<"operator node"<<value[0]<<endl;
                switch (value[0]){
                    case '+':
                        if(node.children[1]==NULL){
                            return 0+Nodeeval(*node.children[0]);
                        }
                        return Nodeeval(*node.children[1])+Nodeeval(*node.children[0]);
                        break;
                    case '-':
                        //cout<<"minus"<<endl;
                        if(node.children[1]==NULL){
                            return 0-Nodeeval(*node.children[0]);
                        }
                        return Nodeeval(*node.children[1])-Nodeeval(*node.children[0]);
                        break;
                    case '*':
                        return Nodeeval(*node.children[1])*Nodeeval(*node.children[0]);
                        break;
                    case '/':
                        left = Nodeeval(*node.children[1]);
                        right = Nodeeval(*node.children[0]);
                        if(right>-0.0000001 && right<0.0000001){
                            cout<<"You can not divide by 0! Make shure your Interval is right!"<<endl;
                            return 0;
                        }
                        return left/right;
                        break;
                    case '^':
                        //cout<<"power"<<endl;
                        if(node.children[0]->data.value=="/"){//special case when you have a division
                            left = Nodeeval(*(node.children[0]->children[1])); //numerator
                            right = Nodeeval(*(node.children[0]->children[0])); //denominator
                            base = Nodeeval(*node.children[1]); //base of the pewer
                            //cout<<base<<"^("<<left<<'/'<<right<<')'<<endl;
                             if(base>-0.0000001 && base<0.0000001) return 0;
                            if(base<0){//for negative x values
                                int gcd = __gcd((int)left,(int)right);
                                left/=gcd; right/=gcd;
                                if(odd(right)){ //if denominator is odd
                                    if(odd(left)){
                                        return -pow(abs(base),left/right); //if left is odd you invert
                                    }else{
                                    return pow(abs(base),left/right); //if left is even you dont have to invert
                                    }
                                }
                                return NAN;
                            }
                        }   
                        left = Nodeeval(*node.children[0]);
                        base = Nodeeval(*node.children[1]);
                        // cout<<base<<'^'<<left<<endl;
                        if(base>-0.0000001 && base<0.0000001) return 0; //its to close to 0 the power fucntion just can not compute
                        return pow(base,left);
                        break;
                    default:
                        //return operator doesnt exits
                        cout<<"Operator doesn't exits"<<endl;
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
                    left=Nodeeval(*node.children[0]);
                    if(left==1){
                        return 0;
                    }
                    return log(Nodeeval(*node.children[1]))/log(left);
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
    return 0;
}

//operator overloading
ostream& operator<<(ostream& os, const Tree& tree){
    tree.print(tree.root,"",true);
    return os;  
}