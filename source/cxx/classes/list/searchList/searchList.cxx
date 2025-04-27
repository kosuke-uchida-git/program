#include"searchList.h"

SearchList::SearchList(List& arg_list):
    node(arg_list.head_()){}

bool SearchList::next(double& nextElement){
    if(node==nullptr)
        return 0;
    nextElement=(*node).element_();
    node=(*node).nextPointer_();
    return 1;
}

bool SearchList::next(){
    if(node==nullptr)
        return 0;
    node=(*node).nextPointer_();
    return 1;
}