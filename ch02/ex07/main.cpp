#include <cstddef>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>

#include "Timer.h"
#include "Random.h"

using fn = std::function<void(const int size)>;
// test a top k function, return the runtime of ms
long testTime(fn fn, int size)
{
    Timer t;

    fn(size);

    return t.elapsed();
}

void exec(fn fn, std::string_view fname)
{
    std::cout << std::setprecision(10) << std::left;
    std::cout << fname << ":\n";
    std::cout << "size\ttime\n";

    for (int size{2}; size <= 100000; size *= 2)
    {
        auto time{testTime(fn, size)};
        std::cout << size << "\t" << time << "\n";
    }
    std::cout << "\n";
}

void f1(int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        ++sum;
}

void f2(int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            ++sum;
}

void f3(int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size * size; ++j)
            ++sum;
}

void f4(int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < i; ++j)
            ++sum;
}

void f5(int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < i * i; ++j)
            for (int k = 0; k < j; ++k)
                ++sum;
}

void f6(int size)
{
    int sum = 0;
    for (int i = 1; i < size; ++i)
        for (int j = 1; j < i * i; ++j)
            if (j % i == 0)
                for (int k = 0; k < j; ++k)
                    ++sum;
}

int main()
{
    exec(f1, "f1");
    exec(f2, "f2");
    // exec(f3, "f3");
    exec(f4, "f4");
    // exec(f6, "f6");
    // exec(f5, "f5");
}
