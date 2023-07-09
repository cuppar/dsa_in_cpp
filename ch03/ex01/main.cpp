#include <iostream>
#include <list>
#include "util.h"

using List = std::list<int>;
void printLots(const List &l, const List &p)
{
    int lastPos{1};
    auto it{l.begin()};
    for (const auto &pos : p)
    {
        if (pos > l.size())
            break;
        auto offset{pos - lastPos};
        lastPos = pos;
        for (int i{0}; i < offset; ++i)
            ++it;
        print(*it, ' ');
    }
    println();
}

void printLots2(const List &l, const List &p)
{
    auto l_it{l.begin()};
    auto p_it{p.begin()};
    int l_pos{1};
    while (l_it != l.end() && p_it != p.end())
    {
        if (*p_it == l_pos)
        {
            print(*l_it, ' ');
            ++p_it;
        }
        ++l_it;
        ++l_pos;
    }
    println();
}

void exec()
{
    List l{3, 5, 7, 9, 11};
    List p{2, 4, 5, 7, 9, 11};
    printLots(l, p);
    printLots2(l, p);
}

int main()
{
    exec();
    return 0;
}
