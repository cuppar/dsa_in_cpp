#include <iostream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <map>
#include "util.h"

template <typename T>
class MinStack
{
public:
    void push(T x)
    {
        if (s.empty())
            min_s.push(x);
        else
            min_s.push(min_s.top() < x ? min_s.top() : x);
        s.push(x);
    }
    const T &top()
    {
        return s.top();
    }

    bool empty()
    {
        return s.empty();
    }

    void pop()
    {
        s.pop();
        min_s.pop();
    }

    const T &findMin()
    {
        return min_s.top();
    }
    void deleteMin()
    {
        // delete first min
        // std::stack<T> temp_s;
        // while (s.top() != min_s.top())
        // {
        //     temp_s.push(s.top());
        //     pop();
        // }
        // pop();
        // while (!temp_s.empty())
        // {
        //     push(temp_s.top());
        //     temp_s.pop();
        // }

        // delete last min
        // T min = min_s.top();
        // std::stack<T> temp_s;
        // while (!min_s.empty() && min_s.top() == min)
        // {
        //     temp_s.push(s.top());
        //     pop();
        // }
        // temp_s.pop();
        // while (!temp_s.empty())
        // {
        //     push(temp_s.top());
        //     temp_s.pop()
        // }

        // delete all min
        T min = min_s.top();
        std::stack<T> temp_s;
        while (!min_s.empty() && min_s.top() == min)
        {
            if (s.top() != min)
                temp_s.push(s.top());
            pop();
        }
        while (!temp_s.empty())
        {
            push(temp_s.top());
            temp_s.pop();
        }
    }

private:
    std::stack<T> s;
    std::stack<T> min_s;
};

void p(MinStack<int> s){
    while (!s.empty())
    {
        println("> ", s.top());
        s.pop();
    }
}

void exec()
{
    MinStack<int> s;
    s.push(2);
    s.push(2);
    s.push(3);
    s.push(2);
    s.push(0);
    s.push(9);
    s.deleteMin();
    println(s.findMin());
    p(s);
    s.deleteMin();
    println(s.findMin());
    p(s);
}

int main()
{
    exec();
    return 0;
}
