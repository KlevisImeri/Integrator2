#include "node.h"

//destructor
Node::~Node(){
    cout<<data<<endl;
    if(children.empty()) return;
    for(auto i : children){
        if(i==NULL) return;
        delete i;
    }
    children.clear();
}

//methods
void Node::addChild(Token data){
    Node* child = new Node(data);
    children.push_back(child);
}
void Node::print(ostream& os, bool lastone) const{
    if(lastone){
        os<<"└──"<<data;  
    }else{
        os<<"├──"<<data;
    }    
}

//operator overloading
ostream& operator<<(ostream& os, const Node& node){
    node.print(os,false);
    return os;
}

