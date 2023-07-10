#include <iostream>
#include <list>
#include "util.h"

using List = std::list<int>;

List n(const List &l1, const List &l2)
{
    auto it1{l1.begin()};
    auto it2{l2.begin()};
    List n;
    while (it1 != l1.end() && it2 != l2.end())
    {
        /* code */
        if (*it1 > *it2)
            ++it2;
        else if (*it1 < *it2)
            ++it1;
        else
        {
            n.push_back(*it1);
            ++it1;
            ++it2;
        }
    }
    return n;
}

List u(const List &l1, const List &l2)
{
    auto it1{l1.begin()};
    auto it2{l2.begin()};
    List n;
    while (it1 != l1.end() && it2 != l2.end())
    {
        /* code */
        if (*it1 > *it2)
        {
            n.push_back(*it2);
            ++it2;
        }
        else if (*it1 < *it2)
        {
            n.push_back(*it1);
            ++it1;
        }
        else
        {
            n.push_back(*it1);
            ++it1;
            ++it2;
        }
    }
    while (it1 != l1.end())
    {
        n.push_back(*it1);
        ++it1;
    }
    while (it2 != l2.end())
    {
        n.push_back(*it2);
        ++it2;
    }
    return n;
}

void exec()
{
    List l1{2, 3, 4, 5};
    List l2{1, 2, 4, 7};
    println(n(l1, l2));
    println(u(l1, l2));
}

int main()
{
    exec();
    return 0;
}
