#include <iostream>
#include "util.h"

template <typename T>
class SLList
{
private:
    struct Node
    {
        T data;
        Node* next;
    };
public:
    SLList()
    {
        init();
    }

    void insert(Node* p, T x)
    {
        Node* n{new Node};
        *n = *p;
        p->data = x;
        p->next = n;

        if (p == tail)
            tail = n;
    }

    void remove(Node* p)
    {
        Node* d {p->next};
        *p = *d;

        if (d == tail)
            tail = p;

        delete d;
    }
    void print()
    {
        Node* p{head->next};

        while (p != tail)
        {
            ::print(p->data, ' ');
            p = p->next;
        }

        println();
    }

    void test()
    {
        for (int i{0}; i < 10; ++i)
            insert(tail, i);

        print();

        remove(head->next);

        remove(head->next->next);

        insert(head->next->next, 99);
        remove(head->next->next->next);
        remove(head->next->next->next->next->next->next->next->next);

        print();
    }
private:
    Node* head;
    Node* tail;

    void init()
    {
        tail = new Node{T{}, nullptr};
        head = new Node{T{}, tail};
    }

};

void exec()
{
    SLList<int> l;
    l.test();
}

int main()
{
    exec();
    return 0;
}
