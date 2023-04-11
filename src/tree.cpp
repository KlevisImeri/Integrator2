#include "tree.h"

//constuctors
Tree::Tree(TokenType type, string str):root(type,str){}
Tree::Tree(Node node):root(node){}


//setter|getters
void Tree::setRoot(const Node& node){
    root = node;
}
Node Tree::getRoot(){
    return root;
}


//methods
void Tree::addChild(Node &child){
    root.addChild(child);
}
void Tree::addChild(Node& parent, Node& child){
    parent.addChild(child);
}
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

//operator overloading
ostream& operator<<(ostream& os, const Tree& tree){
    tree.print(tree.root,"",true);
    return os;  
}