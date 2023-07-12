#include <iostream>
#include <algorithm>
#include <sstream>
#include <list>
#include <map>
#include "util.h"

template <typename T>
class CQueue
{
public:
    bool empty()
    {
        return theArray.size() == 0;
    }
    void push(T x)
    {
        theArray.push_back(x);
    }
    const T &front()
    {
        return theArray[theArray.size() - 1];
    }
    void pop()
    {
        if (empty())
            throw std::runtime_error("pop of empty list");
        theArray.pop_back();
    }
    void find(T x)
    {
        for (int i{(int)theArray.size() - 1}; i >= 0; --i)
        {
            if (theArray[i] == x)
            {
                for (int k{i}; k < theArray.size() - 1; ++k)
                    theArray[k] = theArray[k + 1];
                theArray[theArray.size() - 1] = x;
                return;
            }
        }
    }

private:
    std::vector<T> theArray;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, CQueue<T> s)
{
    os << "{ ";
    const char *sp[] = {"", ", "};
    int i{0};
    while (!s.empty())
    {
        os << sp[i] << s.front();
        s.pop();
        i = 1;
    }
    return os << " }";
}

void exec()
{
    CQueue<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.find(3);
    s.find(1);
    println(s);
}

int main()
{
    exec();
    return 0;
}
