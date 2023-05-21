#include "tree.h"

void Tree::print(ostream& os, const Node<Token>& node, string prefix, bool lastone) const{
    os<< prefix;
    if(lastone){
        node.print(os,true);
    }else{
        node.print(os,false);
    }
    os<<endl;
    if(node.hasChildren()){
        int size = node.numberOfChildren();
        for(int i = 0; i<size; i++){
            if(i+1==size){
                print(os,*(node.getChildAtIndex(i)),prefix+"     ",true);
            }else{
                print(os,*(node.getChildAtIndex(i)),prefix+"     ",false);
            }
            
        }
    }
};

void Tree::buildExpressionTree(vector<Token>& tokens, Node<Token>* node){
    // Nothing left
    if (tokens.empty()) {return;}

    // Special case for root
    if(node==NULL){
        //cout<<"root"<<endl;
        type = EXPRESSION;
        node = &root;
        root.data = tokens.back();
        tokens.pop_back();
    }

    // Creating the tree
    int numchildren = 0;
    if(node->data.type == FUNCTION){
        numchildren = FUNCTION_ARITY.at(node->data.value);
    }else if(node->data.type == OPERATOR){
        numchildren = 2;
    }else{
        return;
    }
    for(int i = 0; i<numchildren; i++){
        if (tokens.empty()){
            throw RuntimeError("Not enough tokens for expression!");
            return;
        }
        node->addChild(tokens.back());
        tokens.pop_back();
        buildExpressionTree(tokens,node->children[i]);
    }
}

double Tree::evaluate(double x, Node<Token>* node){
    if(node==NULL){
        //cout<<"NULL";
        node = &root;
    }
    //out<<*node<<endl;
    if(type!=EXPRESSION){
        throw RuntimeError("You can not evaluate a non expression tree!");
    };
    string value = node->data.value;
    double left, right, base;
    switch (node->data.type) {
        case NUMBER:
           // cout<<"number"<<endl;
            return stod(value);
            break;
        case OPERATOR:
            //cout<<"operator"<<value[0]<<endl;
            right = evaluate(x, node->children[0]);
            left = evaluate(x, node->children[1]);
            switch (value[0]){
                case '+':
                    return left+right;
                    break;
                case '-':
                    //cout<<left<<'-'<<right<<'='<<left-right<<endl;
                    return left-right;
                    break;
                case '*':
                    //cout<<left<<'*'<<right<<endl;
                    return left*right;
                    break;
                case '/':
                    //cout<<left<<'/'<<right<<endl;
                    if(right>-0.0000001 && right<0.0000001){
                        // cout<<"You can not divide by 0! Make shure you Interval is right!";
                        // cout<<"Program will continue but the result will be not a nubmer (nan)!";
                        return NAN;
                    }//here may lead to error rrturn 0;
                    return left/right;
                    break;
                case '^':
                    //special case when you have a division
                    if(node->children[0]->data.value=="/"){
                        base = evaluate(x,node->children[1]); //base of the pewer
                        //cout<<base<<"^("<<left<<'/'<<right<<')'<<endl;
                        if(base>-0.0000001 && base<0.0000001) return 0;
                        if(base<0){//for negative x values
                            left = evaluate(x,node->children[0]->children[1]); //numerator
                            right = evaluate(x,node->children[0]->children[0]); //denominator
                            int gcd = __gcd((int)left,(int)right);
                            left/=gcd; right/=gcd;
                            if((int)right %2){ //if denominator is odd
                                if((int)left %2){
                                    return -pow(abs(base),left/right); //if left is odd you invert
                                }else{
                                    return pow(abs(base),left/right); //if left is even you dont have to invert
                                }
                            }
                            return NAN;
                        }
                    }
                    //cout<<left<<'^'<<right<<endl;
                    if(left>-0.0000001 && left<0.0000001) return 0; //its to close to 0 the power fucntion just can not compute
                    return pow(left,right); //positive x;
                    break;
                default:
                    throw RuntimeError("Operator '"+value+"' is not defined!");
                    break;
            }
        break;
        case FUNCTION:
            right = evaluate(x, node->children[0]);
            //cout<<"function"<<endl;
            if(value=="sin"){
                return sin(right);
            }else if(value=="cos"){
                return cos(right);
            }else if(value=="tan"){
                return tan(right);
            }else if(value=="log"){
                left = evaluate(x, node->children[1]);
                if(right==1){
                    return 0;
                }
              return log(left)/log(right);
            }else{
              throw RuntimeError("Function '"+value+"' is not defined!");
            }
            break;
        case VARIABLE:
            //cout<<"Variable: "<<x<<endl;
            return x;
            break;
        case EULER:
            //cout<<"Euler"<<endl;
            return 2.71828;
            break;
        case PI:
            //cout<<"PI"<<endl;
            return 3.14159265359;
            break;
        default:
            throw RuntimeError("Unknown token type!");
            break;
    }
    return 0;
}   

//operator overloading
ostream& operator<<(ostream& os, const Tree& tree){
    tree.print(os,tree.root,"",true);
    return os;  
}