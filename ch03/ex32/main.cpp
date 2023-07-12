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
    CQueue() : front{nullptr}, rear{nullptr} {}
    bool empty()
    {
        return front == nullptr && rear == nullptr;
    }
    void enqueue(T x)
    {
        if (empty())
            front = rear = new Node{x, nullptr};
        else
            rear = rear->next = new Node{x, nullptr};
    }
    T dequeue()
    {
        if (empty())
            throw std::runtime_error("dequeue of empty queue");
        Node *d{front};
        T ret{d->data};
        if (front == rear)
            front = rear = nullptr;
        else
            front = front->next;
        delete d;
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
        os << sp[i] << s.dequeue();
        i = 1;
    }
    return os << " }";
}

void exec()
{
    CQueue<int> s;
    s.enqueue(1);
    s.enqueue(2);
    s.enqueue(3);
    s.dequeue();
    println(s);
}

int main()
{
    exec();
    return 0;
}
