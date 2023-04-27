#include "node.h"

//constructors
Node::Node(){}
Node::Node(Token data):data(data),children(std::vector<Node*>(0)){}
Node::Node(TokenType type, string str):data(type,str){}
//destructor
Node::~Node(){
    for(auto i : children){
        delete i;
    }
}

//seters|geters
void Node::setData(Token token){
    data = token;
}
Token Node::getData(){
    return data;
}
vector<Node*> Node::getChildren(){
    return children;
}
Node* Node::getChildAtIndex(int i) const{
    return children[i];
}


//methods
int Node::numberOfChildren() const{
    return children.size();
}
bool Node::hasChildren() const{
    return children.size()!=0;
}
void Node::addChild(Token data){
    Node* child = new Node(data);
    children.push_back(child);
}
void Node::print(bool lastone) const{
    if(lastone){
        cout<<"└──"<<data;  
    }else{
        cout<<"├──"<<data;
    }
    
}


//operator overloading
ostream& operator<<(ostream& os, const Node& node){
    node.print(false);
    return os;
}

