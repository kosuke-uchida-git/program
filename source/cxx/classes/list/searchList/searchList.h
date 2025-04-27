#include"../list/list.h"

#ifndef SEARCH_LIST
#define SEARCH_LIST

class SearchList{
    protected:
        Node* node;
    public:
        SearchList(List& arg_list);
        bool next(double& nextElement);
        bool next();
};

#endif