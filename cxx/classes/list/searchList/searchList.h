#include"../list/list.h"

class SearchList{
    protected:
        Node* node;
    public:
        SearchList(List& arg_list);
        bool next(double& nextElement);
        bool next();
};