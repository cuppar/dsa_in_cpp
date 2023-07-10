#include <iostream>
#include <list>
#include "util.h"

using List = std::list<int>;
using It = List::iterator;

int josephus(List &l, It start, int m)
{
    int n = l.size();
    if (n == 1)
        return *l.begin();

    auto it{start};
    if (it == l.end())
        it = l.begin();

    int move{m % n};
    for (int i{0}; i < move; ++i)
    {
        ++it;
        if (it == l.end())
            it = l.begin();
    }
    println("earse ", *it);
    it = l.erase(it);
    return josephus(l, it, m);
}

int josephus2(List &l, It start, int m)
{
    auto it{start};

    while (true)
    {
        int n = l.size();
        if (n == 1)
            return *l.begin();

        if (it == l.end())
            it = l.begin();

        int move{m % n};
        for (int i{0}; i < move; ++i)
        {
            ++it;
            if (it == l.end())
                it = l.begin();
        }
        println("earse ", *it);
        it = l.erase(it);
    }
}

void exec()
{
    List l{1, 2, 3, 4, 5};
    println(josephus2(l, l.begin(), 0));
    l = {1, 2, 3, 4, 5};
    println(josephus2(l, l.begin(), 1));
}

int main()
{
    exec();
    return 0;
}
