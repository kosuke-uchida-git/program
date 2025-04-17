#include"node.h"

Node::Node():
    element(0.0),
    nextPointer(nullptr){}

Node::Node(double arg_element):
    element(arg_element),
    nextPointer(nullptr){}

Node::Node(double arg_element, Node* arg_nextPointer):
    element(arg_element),
    nextPointer(arg_nextPointer){}

double Node::element_() const{
    return element;
}

double& Node::element_(){
    return element;
}

Node* Node::nextPointer_() const{
    return nextPointer;
}

Node*& Node::nextPointer_(){
    return nextPointer;
}

void Node::print(){
    std::cout<<"address    : "<<this<<std::endl;
    std::cout<<"element    : "<<element<<std::endl;
    std::cout<<"nextPointer: ";
    if(nextPointer==nullptr)
        std::cout<<"nullptr";
    else
        std::cout<<nextPointer;
    std::cout<<std::endl;
}