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
    CQueue(int capacity)
        : theArray{std::vector<T>(capacity)},
          front{0},
          rear{0},
          capacity{capacity} {}
    bool empty()
    {
        return front == rear;
    }
    bool full()
    {
        return (rear + 1) % capacity == front;
    }
    void enqueue(T x)
    {
        if (full())
            throw std::runtime_error("enqueue on a full queue");
        theArray[rear] = x;
        rear = (rear + 1) % capacity;
    }
    T dequeue()
    {
        if (empty())
            throw std::runtime_error("dequeue on a empty queue");
        auto ret{theArray[front]};
        front = (front + 1) % capacity;
        return ret;
    }

private:
    std::vector<T> theArray;
    int front;
    int rear;
    int capacity;
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
    CQueue<int> s(10);
    for (int i{1}; i < 10; ++i)
        s.enqueue(i);
    s.dequeue();
    s.enqueue(99);
    println(s);
}

int main()
{
    exec();
    return 0;
}
