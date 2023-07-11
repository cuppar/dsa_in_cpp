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
            else if (p->data > x)
                return false;
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
            else if (p->data > x)
            {
                Node *n = new Node{x, nullptr};
                prev->next = n;
                n->next = p;
                return;
            }
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
            else if (p->data > x)
                return;
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
        l.add(20 - i);
    println(l.size());
    l.print();
    l.remove(12);
    l.print();
    l.remove(14);
    l.print();
    l.remove(13);
    l.print();
    l.add(113);
    l.print();
    l.add(13);
    l.print();
}

int main()
{
    exec();
    return 0;
}
