#include<iostream>

class Node{
    protected:
        double element;
        Node* nextPointer;
    public:
        Node();
        Node(double arg_element);
        Node(double arg_element, Node* arg_nextPointer);

        double element_() const;
        double& element_();
        Node* nextPointer_() const;
        Node*& nextPointer_();

        void print();
};