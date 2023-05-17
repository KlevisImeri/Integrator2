#include "lexer.h"


Lexer::Lexer():str(""){}
Lexer::Lexer(string str):str(str){}
Lexer::Lexer(const Lexer& lexer):str(lexer.str){}

void Lexer::askForFunction(){
    do{
        //Wait for the user to read the error
        char n;
        do{
            cout<<"Press enter to continue!";
            cin.ignore();
            cin.get(n);
        }while(n!='\n');

        system("clear");
        cout<<"Type the function:";
        cin>>str;
    }while(!Lexer::tokenizeValid());
}
void Lexer::setString(const string& strin){
    str=strin;
}
bool Lexer::tokenize(){
    tokenList.clear();
    int i = 0;
    int size = str.length();
    while (i < size){
        if (isdigit(str[i])) {  // number
            string number = "";
            while (i < size && (isdigit(str[i]) || str[i] == '.')) {
                number += str[i];
                i++;
            }
            tokenList.push_back({TokenType::NUMBER, number});
        } else if (isalpha(str[i])) { // identifier or function name
            if(!tokenList.empty() && (tokenList.back().type == TokenType::NUMBER || tokenList.back().type == TokenType::PAREN_RIGHT)){
                tokenList.push_back({TokenType::OPERATOR, "*"});
            }  
            string name = "";
            while (i < size && (isalnum(str[i]) || str[i] == '_')){
                name += str[i];
                i++;
            }
            if (name == "x") {  // treat "x" as identifier
                tokenList.push_back({TokenType::VARIABLE, name});
            }else if (name == "e") {  // treat "e" as identifier
                Token token(TokenType::EULER, name);
                tokenList.push_back(token);
            }else if (name == "pi") {  // treat "pi" as identifier
                Token token(TokenType::PI, name);
                tokenList.push_back(token);
            }else {  // treat other identifiers as function names
                Token token(TokenType::FUNCTION, name);
                tokenList.push_back(token);
            }
        } else if (str[i] == '+' || str[i] == '-') {  // operator type1
            if(!tokenList.empty() && tokenList.back().type == TokenType::PAREN_LEFT){
                tokenList.push_back({TokenType::NUMBER, "0"});
            } 
            tokenList.push_back({TokenType::OPERATOR, string(1, str[i])});
            i++; 
        } else if (str[i] == '*' || str[i] == '/' || str[i] == '^') {  // operator type2
            tokenList.push_back({TokenType::OPERATOR, string(1, str[i])});
            i++; 
        } else if (str[i] == '('){  // parentheses
            if(!tokenList.empty() && tokenList.back().type == TokenType::NUMBER){
                tokenList.push_back({TokenType::OPERATOR, "*"});
            }  
            tokenList.push_back({TokenType::PAREN_LEFT, string(1, str[i])});
            i++;
        } else if (str[i] == ')'){  // parentheses
            Token token(TokenType::PAREN_RIGHT, string(1, str[i]));
            tokenList.push_back(token);
            i++;
        } else if (str[i] == ','){
            Token token(TokenType::COMA, string(1, str[i]));
            tokenList.push_back(token);
            i++;
        }else if (isspace(str[i])) {  // whitespace
            i++;
        } else {  // invalid character
            cout<<"Invalid character: "<<string(1, str[i])<<endl;
            return false;
            //throw runtime_error("Invalid character: " + string(1, str[i]));
        }
    }

    return true;
}
bool Lexer::tokenizeValid(){
    tokenList.clear();
    if(!tokenize()){
        return false;
    } 

    int openParen = 0;
    int closeParen = 0;
    for(int i = 0; i<tokenList.size(); i++){
        if(tokenList[i].value == "("){
            openParen++;
        }else if(tokenList[i].value == ")"){
            closeParen++;
        }else if(tokenList[i].value == "^" || tokenList[i].value == "/"|| tokenList[i].value == "*"){
            //^x /x *x
            if(i==0){
                cout<<"The operators '^''*''/' take a value in both sides!";
                return false;
            }
            //*- *^ ...
            if(tokenList[i+1].type==TokenType::OPERATOR){
                cout<<"You have 2 operators one after the other!";
                return false;
            }
        }else if(tokenList[i].value == "-" || tokenList[i].value == "+"){
            //-+
            if(tokenList[i+1].type==TokenType::OPERATOR){
                cout<<"You have 2 operators one after the other!";
                return false;
            }
        }
        //divide by zero (Not using b.search)
        if(tokenList[i].value=="/"){
            if(stod(tokenList[i+1].value)==0){
                cout<<"You can't divide by 0!"<<endl;
                return false;
            }
        }

        //you cant have 2.333/4.222

        //some function have several inputs
        // if(tokenList[i].type==TokenType::FUNCTION){
        //     int parameters = FUNCTION_ARITY.at(tokenList[i].value);
        //     int comas=0;
        //     for(int j=i; tokenList[i].type != TokenType::PAREN_RIGHT; j++){
        //         if(tokenList[j].type == TokenType::COMA){
        //             comas++;
        //         }
        //     }

        //     if(parameters > comas){  
        //         cout<<"The function takes "<< parameters << " parameters"<<endl;
        //         return false;
        //     }

        // }

        return true;
    }
    //parentheses
    if(openParen > closeParen){
        cout<<"You have more '(' than ')'"<<endl;
        return false;
    }else if(openParen < closeParen){
        cout<<"You have more ')' than '('"<<endl;
        return false;
    }
    //check '(' or NUMBER or VARIABLE for OPERATORS '-''+'


    //2. x surrounded by operands or nothing

    return true;
}

vector<Token> Lexer::getTokenList(){return tokenList;}

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