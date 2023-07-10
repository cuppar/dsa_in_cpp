#include <iostream>
#include <list>
#include "util.h"

template <typename Iterator, typename Object>
Iterator myfind(Iterator start, Iterator end, const Object &x)
{
    while (start != end)
    {
        if (*start == x)
            return start;
        ++start;
    }
    return start;
}

using List = std::list<int>;

void exec()
{
    List l{1, 2, 3, 4, 1, 2, 3, 4};
    if (auto found = myfind(l.begin(), l.end(), 3);
        found != l.end())
    {
        println("found ", *found);
    }
}

int main()
{
    exec();
    return 0;
}
