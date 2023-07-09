#include <iostream>
#include <list>
#include "util.h"

using List = std::list<int>;
using It = List::iterator;
void adjust(List &l, const It &it)
{
    if (std::next(it) == l.end())
        return;
    auto cur_it{l.begin()};
    It pre_it;
    while (cur_it != it)
    {
        pre_it = cur_it;
        ++cur_it;
    }

    pre_it._Ptr->_Next = it._Ptr->_Next;
    it._Ptr->_Next = it._Ptr->_Next->_Next;
    pre_it._Ptr->_Next->_Next = it._Ptr;
}

void exec()
{
    List l{3, 5, 7, 9, 11};
    println(l);
    adjust(l, std::next(l.begin()));
    println(l);
}

int main()
{
    exec();
    return 0;
}
