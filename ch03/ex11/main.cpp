#include <iostream>
#include <algorithm>
#include "util.h"

template <typename T>
class SLList
{
private:
    struct Node
    {
        T data;
        Node *next;
    };

public:
    SLList()
    {
        init();
    }

    int size()
    {
        Node *p = head;
        int size{0};
        while (p = p->next)
            ++size;
        return size;
    }

    void print()
    {
        Node *p = head;
        while (p = p->next)
            ::print(p->data, ' ');
        ::println();
    }

    bool has(T x)
    {
        Node *p = head;
        while (p = p->next)
            if (p->data == x)
                return true;
        return false;
    }

    void add(T x)
    {
        Node *p = head;
        Node *prev = head;
        while (p = p->next)
        {
            if (p->data == x)
                return;
            prev = p;
        }
        Node *n = new Node{x, nullptr};
        prev->next = n;
    }

    void remove(T x)
    {
        Node *p = head;
        Node *prev = head;
        while (p = p->next)
        {
            if (p->data == x)
            {
                prev->next = p->next;
                delete p;
                return;
            }
            prev = p;
        }
    }

private:
    Node *head;
    void init()
    {
        head = new Node;
        head->next = nullptr;
    }
};

void exec()
{
    SLList<int> l;
    println(l.size());
    for (int i{0}; i < 10; ++i)
        l.add(i);
    println(l.size());
    l.print();
    l.remove(-1);
    l.remove(3);
    l.print();
    println(l.size());
}

int main()
{
    exec();
    return 0;
}
