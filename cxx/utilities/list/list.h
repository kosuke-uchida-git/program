#include"node.h"

class List{
    protected:
        Node* head;
        Node* tail;
    public:
        List(double arg_element);
        ~List();

        Node* head_() const;
        Node* tail_() const;

        void print();

        void addHead(double arg_element);
        void addTail(double arg_element);
};