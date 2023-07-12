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
        Node *prev;
        Node *next;
    };

public:
    CQueue()
        : front{nullptr},
          rear{nullptr}
    {
    }
    bool empty()
    {
        return front == nullptr && rear == nullptr;
    }
    void push(T x)
    {
        if (empty())
            front = rear = new Node{x, nullptr, nullptr};
        else
            front = front->prev = new Node{x, nullptr, front};
    }
    T pop()
    {
        if (empty())
            throw std::runtime_error("pop of empty deque");
        auto p{front};
        T ret{p->data};
        if (front == rear)
            front = rear = nullptr;
        else
        {
            front = front->next;
            front->prev = nullptr;
        }
        delete p;
        return ret;
    }
    void inject(T x)
    {
        if (empty())
            front = rear = new Node{x, nullptr, nullptr};
        else
            rear = rear->next = new Node{x, rear, nullptr};
    }
    T eject()
    {
        if (empty())
            throw std::runtime_error("eject of empty deque");
        auto p{rear};
        T ret{p->data};
        if (front == rear)
            front = rear = nullptr;
        else
        {
            rear = rear->prev;
            rear->next = nullptr;
        }
        delete p;
        return ret;
    }

private:
    Node *front;
    Node *rear;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, CQueue<T> s)
{
    os << "{ ";
    const char *sp[] = {"", ", "};
    int i{0};
    while (!s.empty())
    {
        os << sp[i] << s.eject();
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
    s.inject(5);
    s.inject(6);
    s.inject(7);
    println(s);
}

int main()
{
    exec();
    return 0;
}
