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
            Token token(TokenType::NUMBER, number);
            tokenList.push_back(token);
        } else if (isalpha(str[i])) {  // identifier or function name
            string name = "";
            while (i < size && (isalnum(str[i]) || str[i] == '_')) {
                name += str[i];
                i++;
            }
            if (name == "x") {  // treat "x" as identifier
                Token token(TokenType::VARIABLE, name);
                tokenList.push_back(token);
            }else if (name == "e") {  // treat "x" as identifier
                Token token(TokenType::EULER, name);
                tokenList.push_back(token);
            }else if (name == "pi") {  // treat "x" as identifier
                Token token(TokenType::PI, name);
                tokenList.push_back(token);
            }else {  // treat other identifiers as function names
                Token token(TokenType::FUNCTION, name);
                tokenList.push_back(token);
            }
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {  // operator
            Token token(TokenType::OPERATOR, string(1, str[i]));
            tokenList.push_back(token);
            i++;
        } else if (str[i] == '('){  // parentheses
            Token token(TokenType::PAREN_LEFT, string(1, str[i]));
            tokenList.push_back(token);
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
    

    //3.  divide by zero (Not using b.search)
    for(int i = 0; i<tokenList.size(); i++){
        if(tokenList[i].type==TokenType::NUMBER && tokenList[i].value== "0"){
            cout<<"You can't divide by 0!"<<endl;
            return false;
        }
    }

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