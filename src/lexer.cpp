#include "lexer.h"

using namespace std;

Lexer::Lexer():str(""),pT(NULL),Tsize(0){}

Lexer::Lexer(string str):str(str),pT(NULL),Tsize(0){}

Lexer::Lexer(const Lexer& lexer):str(lexer.str),Tsize(lexer.Tsize){
    pT = new Token[Tsize];
    for(int i = 0; i<Tsize; i++){
        pT[i]=lexer.pT[i];
    }
}
Lexer::~Lexer(){
    delete[] pT;
}
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
    }while(!Lexer::isFunctionValid());
}
void Lexer::setString(const string& strin){
    str=strin;
}
bool Lexer::tokenize(){
    vector<Token> tokenList;  // list of tokens
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
            } else {  // treat other identifiers as function names
                Token token(TokenType::FUNCTION, name);
                tokenList.push_back(token);
            }
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {  // operator
            Token token(TokenType::OPERATOR, string(1, str[i]));
            tokenList.push_back(token);
            i++;
        } else if (str[i] == '('|| str[i] == ')'){  // parentheses
            Token token(TokenType::PARENTHESES, string(1, str[i]));
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
    // store token list
    Tsize = tokenList.size();
    pT = new Token[Tsize];
    for (int i = 0; i < Tsize; i++) {
        pT[i] = tokenList[i];
    }

    return true;
}
bool Lexer::isFunctionValid(){
    //invalid character
    // try {
    //     tokenize();
    // } catch (const exception& e) {  
    //     cout << e.what() << endl;
    //     return false;
    // }
    return tokenize();

    int openParen = 0;
    int closeParen = 0;
    for(int i = 0; i<Tsize; i++){
        if(pT[i].value == "("){
            openParen++;
        }else if(pT[i].value == ")"){
            closeParen++;
        }else if(pT[i].value == "^" || pT[i].value == "/"|| pT[i].value == "*"){
            //^x /x *x
            if(i==0){
                cout<<"The operators '^''*''/' take a value in both sides!";
                return false;
            }
            //*- *^ ...
            if(pT[i+1].type==TokenType::OPERATOR){
                cout<<"You have 2 operators one after the other!";
                return false;
            }
        }else if(pT[i].value == "-" || pT[i].value == "+"){
            //-+
            if(pT[i+1].type==TokenType::OPERATOR){
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
    for(int i = 0; i<Tsize; i++){
        if(pT[i].type==TokenType::NUMBER && pT[i].value== "0"){
            cout<<"You can't divide by 0!"<<endl;
            return false;
        }
    }

    return true;
}
void Lexer::print() const{
    cout<<"Lexer{"<<endl;
    cout<<" Function: "<<str<<endl;
    cout<<" Tokens: {";
    for(int i = 0; i<Tsize; i++){
        if(i%3==0){
            cout<<endl<<"     ";
        }
        cout<<pT[i]<<" ";
    }
    cout<<endl<<" }"<<endl<<"}"<<endl;
}