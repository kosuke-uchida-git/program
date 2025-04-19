#include"list.h"

List::List(double arg_element){
    Node* firstNode=new Node(arg_element);
    head=firstNode;
    tail=firstNode;
}

List::~List(){
    Node* tmp1_node=head;
    Node* tmp2_node;
    while(1){
        tmp2_node=(*tmp1_node).nextPointer_();
        delete tmp1_node;
        if(tmp2_node==nullptr)
            break;
        tmp1_node=tmp2_node;
    }
}

Node* List::head_() const{
    return head;
}

Node* List::tail_() const{
    return tail;
}

void List::print(){
    std::cout<<"head: "<<head<<std::endl;
    std::cout<<"tail: "<<tail<<std::endl;
    Node* tmp_node=head;
    int nodeCount=1;
    while(1){
        std::cout<<std::endl;
        std::cout<<"Node "<<nodeCount<<std::endl;
        (*tmp_node).print();
        tmp_node=(*tmp_node).nextPointer_();

        if(tmp_node==nullptr)
            break;

        nodeCount++;
    }
}

void List::addHead(double arg_element){
    Node* newNode=new Node(arg_element);
    (*newNode).nextPointer_()=head;
    head=newNode;
}

void List::addTail(double arg_element){
    Node* newNode=new Node(arg_element);
    (*tail).nextPointer_()=newNode;
    tail=newNode;
}