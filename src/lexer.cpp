#include "lexer.h"

void Lexer::askForFunction(){
    bool success = false;
    char n;
    while (!success) {
        success = true; 
        system("clear");
        cout<<"Type the function:";
        cin>>str;
        try{
            tokenize();
        }catch (const exception& e) {
            success = false;  
            cerr<<e.what()<<endl;
        }
        // Wait till the user reads
        if(!success){
            cout<<"Press enter to continue!";
            do{
                cin.ignore();
                cin.get(n);
            }while(n!='\n');
        }
    }
}
    

void Lexer::tokenize(){
    // Preperation
    tokenList.clear();
    int i = 0;
    int size = str.length();
    int Paren_left = 0;
    int Paren_right = 0;

    // Tokenizing
    while (i < size){

        // Number
        if (isdigit(str[i])) {  
            string number = "";
            while (i < size && (isdigit(str[i]) || str[i] == '.')) {
                number += str[i];
                i++;
            }
            if(!tokenList.empty() && tokenList.back().value == "/" && stod(number)==0){
                throw DivByZero();
            }
            tokenList.push_back({NUMBER, number});
        } 

        // Identifier or function name
        else if (isalpha(str[i])) {
            // 1. <num>x -> <num>*x 
            // 2. )x -> )*x
            if(!tokenList.empty() && (tokenList.back().type == NUMBER || tokenList.back().type == PAREN_RIGHT)){
                if(tokenList.back().type == OPERATOR){
                    throw RuntimeError("You have 2 operators one after the other!");
                } 
                tokenList.push_back({OPERATOR, "*"});
            }  
            // Function and constants
            string name = "";
            while (i < size && (isalnum(str[i]) || str[i] == '_')){
                name += str[i];
                i++;
            }
            //x
            if (name == "x") { 
                tokenList.push_back({VARIABLE, name});
            }
            //e            
            else if (name == "e") {  
                Token token(EULER, name);
                tokenList.push_back(token);
            }
            //pi
            else if (name == "pi") {  
                Token token(PI, name);
                tokenList.push_back(token);
            }
            //function
            else {
                if(FUNCTION_ARITY.find(name) == FUNCTION_ARITY.end()){
                    throw RuntimeError("Invalid function name: "+name);
                }
                Token token(FUNCTION, name);
                tokenList.push_back(token);
            }
        } 

        // Operator +|-
        else if (str[i] == '+' || str[i] == '-') {  
            // (x) -> (0+x)
            if(tokenList.empty() || tokenList.back().type == PAREN_LEFT){
                tokenList.push_back({NUMBER, "0"});
            }else if(tokenList.back().type == OPERATOR){
                throw RuntimeError("You have 2 operators one after the other!");
            }else if(tokenList.back().type == COMA || tokenList.back().type == PAREN_LEFT){
                throw RuntimeError(string("The left of operator '")+str[i]+string("' is a wrong token!"));
            }else if(i+1>=size){
                throw RuntimeError(string("The right of operator '")+str[i]+string("' is a empty!"));
            }
            tokenList.push_back({OPERATOR, str[i]});
            i++; 
        } 

        // Operator *|/
        else if (str[i] == '*' || str[i] == '/' || str[i] == '^') { 
            //^x /x *x
            if(tokenList.empty()){
                throw RuntimeError("The operators '^''*''/' take a value in both sides!");
            }else if(tokenList.back().type == OPERATOR){
                throw RuntimeError("You have 2 operators one after the other!");
            }else if(tokenList.back().type == COMA || tokenList.back().type == PAREN_LEFT){
                throw RuntimeError(string("The left of operator '")+str[i]+string("' is a wrong token!"));
            }else if(i+1>=size){
                throw RuntimeError(string("The right of operator '")+str[i]+string("' is a empty!"));
            }
            tokenList.push_back({OPERATOR, str[i]});
            i++; 
        } 
        
        // (
        else if (str[i] == '('){
            // <num>() => <num>*() 
            if(!tokenList.empty() && tokenList.back().type == NUMBER){
                tokenList.push_back({OPERATOR, "*"});
            }  
            tokenList.push_back({PAREN_LEFT, str[i]});
            Paren_left++;
            i++;
        } 
        
        // )
        else if (str[i] == ')'){ 
            tokenList.push_back({PAREN_RIGHT, str[i]});
            Paren_right++;
            i++;
        }
        
        // ,
        else if (str[i] == ','){
            tokenList.push_back({COMA, str[i]});
            i++;
        }
        
        // ' '
        else if (isspace(str[i])) {  
            i++;
        } 
        
        // invalid character
        else{ 
            throw InvalidStringInput(str[i]);
            break;
        }
    }
    //    EXCEPTION HANDLING
    //parentheses
    if(Paren_right!=Paren_left) throw RuntimeError("Mismached '(' and ')'!");
    // arity of the functions
    try{
        for (int i = 0; i < tokenList.size(); i++) {
            if (tokenList[i].type == FUNCTION) {
                validArity(tokenList[i], i);
            }
        }
    }catch(const exception& e) {
        throw;  
    }

    return;
}

void Lexer::validArity(Token token, int pos){
    int commas = 0;
    bool parameters = false;

    if(tokenList[pos+1].type != PAREN_LEFT) throw RuntimeError("Functions should have '()' at the end!");

    for (int j=pos+2; tokenList[j].type != PAREN_RIGHT; j++){
        if (tokenList[j].type == COMA) {
            // Check if the comma is in the right place
            TokenType left = tokenList[j-1].type;
            TokenType right = tokenList[j+1].type;
            if (left != PAREN_LEFT && left!=OPERATOR && right!= PAREN_RIGHT) {
                commas++;
            } else {
                throw RuntimeError("Function parameters and ',' are in the wrong place");
            }
        }else if(!parameters) {
            parameters = true;
        }
    }

    int arity = 0;
    if(parameters){
        arity = 1 + commas;
    }
    //cout<<"arrity: "<<arity<<endl;
    if (arity != FUNCTION_ARITY.at(token.value)) {
        throw RuntimeError("The arity of the function is not correct!");
    }
}


void Lexer::print() const{
    cout<<"Lexer{"<<endl;
    cout<<" Function: "<<str<<endl;
    cout<<" Tokens: {";
    for(int i = 0; i<tokenList.size(); i++){
        if(i%3==0){
            cout<<endl<<"     ";
        }
        cout<<tokenList[i]<<" ";
    }
    cout<<endl<<" }"<<endl<<"}"<<endl;
}