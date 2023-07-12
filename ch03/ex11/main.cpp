#include <iostream>
#include <algorithm>
#include "util.h"

template <typename T>
class SLList
{
public:
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

    int size() const
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
    void reverse() const
    {
        if (size() == 0)
            return;
        Node *last = nullptr;
        Node *p;
        while (true)
        {
            p = head->next;
            while (p->next != last)
                p = p->next;
            ::print(p->data, ' ');
            last = p;
            if (p == head->next)
                return;
        }
    }

public:
    Node *head;
    void init()
    {
        head = new Node;
        head->next = nullptr;
    }
};

void reverse(SLList<int>::Node *p)
{
    if (p == nullptr)
        return;

    reverse(p->next);
    print(p->data);
}

void exec()
{
    SLList<int> l;
    println(l.size());
    for (int i{0}; i < 10; ++i)
        l.add(i);
    println(l.size());
    l.print();
    reverse(l.head->next);
    println();
    l.reverse();
    // l.remove(-1);
    // l.remove(3);
    // l.print();
    // println(l.size());
}

int main()
{
    exec();
    return 0;
}
