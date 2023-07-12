#include <iostream>
#include <algorithm>
#include <sstream>
#include <list>
#include <map>
#include "util.h"

template <typename T>
class ThreeStack
{
public:
    ThreeStack(int size)
        : theArray{std::vector<T>(size)},
          leftTop{0},
          rightTop{size - 1}
    {
    }

    bool left_empty()
    {
        return leftTop == 0;
    }
    bool right_empty()
    {
        return rightTop == theArray.size() - 1;
    }
    void push_left(T x)
    {
        assertNotOverflow();
        theArray[leftTop++] = x;
    }
    void push_right(T x)
    {
        assertNotOverflow();
        theArray[rightTop--] = x;
    }
    const T &left()
    {
        if (left_empty())
            throw std::runtime_error("left stack empty");
        return theArray[leftTop - 1];
    }
    const T &right()
    {
        if (right_empty())
            throw std::runtime_error("right stack empty");
        return theArray[rightTop + 1];
    }
    void pop_left()
    {
        if (left_empty())
            throw std::runtime_error("left stack empty");
        --leftTop;
    }
    void pop_right()
    {
        if (right_empty())
            throw std::runtime_error("right stack empty");
        ++rightTop;
    }

private:
    std::vector<T> theArray;
    int leftTop;
    int rightTop;

    void assertNotOverflow() const
    {
        if (leftTop - 1 == rightTop)
            throw std::runtime_error("stack overflow");
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, ThreeStack<T> s)
{
    os << "left: { ";
    const char *sp[] = {"", ", "};
    int i{0};
    while (!s.left_empty())
    {
        os << sp[i] << s.left();
        s.pop_left();
        i = 1;
    }
    os << " }, right: { ";
    i = 0;
    while (!s.right_empty())
    {
        os << sp[i] << s.right();
        s.pop_right();
        i = 1;
    }
    return os << " }";
}

void exec()
{
    ThreeStack<int> s(5);
    s.push_left(1);
    s.push_left(2);
    s.push_right(1);
    s.push_right(2);
    s.push_right(3);
    s.pop_left();
    s.push_right(4);
    println(s);
}

int main()
{
    exec();
    return 0;
}
