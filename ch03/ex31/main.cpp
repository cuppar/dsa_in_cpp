#include <iostream>
#include <algorithm>
#include <sstream>
#include <list>
#include <map>
#include "util.h"

template <typename T>
class CQueue
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

public:
    CQueue() : stack{nullptr} {}
    bool empty()
    {
        return stack == nullptr;
    }
    void push(T x)
    {
        stack = new Node{x, stack};
    }
    T &top()
    {
        return stack->data;
    }
    void pop()
    {
        if (empty())
            throw std::runtime_error("pop of empty stack");
        auto d{stack};
        stack = stack->next;
        delete d;
    }

private:
    Node *stack;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, CQueue<T> s)
{
    os << "{ ";
    const char *sp[] = {"", ", "};
    int i{0};
    while (!s.empty())
    {
        os << sp[i] << s.top();
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
    s.pop();
    println(s.top());
    println(s);
}

int main()
{
    exec();
    return 0;
}
