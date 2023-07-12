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
    CQueue()
    {
        init();
    }
    bool empty()
    {
        return head->next == nullptr;
    }
    void push(T x)
    {
        head->next = new Node{x, head->next};
    }
    const T &front()
    {
        return head->next->data;
    }
    void pop()
    {
        if (empty())
            throw std::runtime_error("pop of empty list");
        head->next = head->next->next;
    }
    void find(T x)
    {
        Node *p{head->next};
        Node *last{nullptr};
        while (p && p->data != x)
        {
            last = p;
            p = p->next;
        }
        if (p)
        {
            last->next = p->next;
            p->next = head->next;
            head->next = p;
        }
    }

private:
    Node *head;
    void init()
    {
        head = new Node{T{}, nullptr};
    }
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
