#include <cstddef>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <utility>

#include "Timer.h"
#include "Random.h"

using fn = std::function<void(const int size)>;
// test a top k function, return the runtime of ms
long testTime(fn fn, int size)
{
    Timer t;

    for (int i{0}; i < 10; ++i)
        fn(size);

    return t.elapsed() / 10;
}

void f1(int size)
{
    std::vector<int> v(size);
    for (int i{0}; i < v.size(); ++i)
    {
        int x{Random::get(1, size)};
        bool used = false;
        for (int j{0}; j < i; ++j)
        {
            if (v[j] == x)
            {
                used = true;
                break;
            }
        }
        if (used)
        {
            --i;
            continue;
        }
        else
            v[i] = x;
    }

    // print
    // for (int x : v)
    //     std::cout << x << ' ';
    // std::cout << '\n';
}

void f2(int size)
{
    std::vector<int> v(size);
    std::vector<bool> used(size);
    for (int i{0}; i < v.size(); ++i)
    {
        int x{Random::get(1, size)};
        if (used[x - 1])
        {
            --i;
            continue;
        }
        else
        {
            v[i] = x;
            used[x - 1] = true;
        }
    }

    // print
    // for (int x : v)
    //     std::cout << x << ' ';
    // std::cout << '\n';
}

void f3(int size)
{
    std::vector<int> v(size);
    for (int i{0}; i < v.size(); ++i)
    {
        v[i] = i + 1;
    }

    for (int i{1}; i < v.size(); ++i)
    {
        int random = Random::get(0, i);
        std::swap(v[i], v[random]);
    }

    // print
    // for (int x : v)
    //     std::cout << x << ' ';
    // std::cout << '\n';
}

void exec1()
{
    std::cout << std::setprecision(10) << std::left;
    std::cout << "f1"
              << ":\n";
    std::cout << "size\ttime\n";

    for (int size{250}; size <= 2'000; size *= 2)
    {
        auto time{testTime(f1, size)};
        std::cout << size << "\t" << time << "\n";
    }
    std::cout << "\n";
}

void exec2()
{
    std::cout << std::setprecision(10) << std::left;
    std::cout << "f2"
              << ":\n";
    std::cout << "size\ttime\n";

    for (int size{25'000}; size <= 800'000; size *= 2)
    {
        auto time{testTime(f2, size)};
        std::cout << size << "\t" << time << "\n";
    }
    std::cout << "\n";
}

void exec3()
{
    std::cout << std::setprecision(10) << std::left;
    std::cout << "f3"
              << ":\n";
    std::cout << "size\ttime\n";

    for (int size{100'000}; size <= 6'400'000; size *= 2)
    {
        auto time{testTime(f3, size)};
        std::cout << size << "\t" << time << "\n";
    }
    std::cout << "\n";
}

int main()
{
    exec1();
    exec2();
    exec3();
}
