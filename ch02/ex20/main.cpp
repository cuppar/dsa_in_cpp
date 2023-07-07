#include <cmath>
#include "util.h"
#include <iostream>

bool isprime(int n)
{
    if (n <= 1)
        return false;

    bool isprime_ = true;

    for (int i{2}; i <= std::sqrt(n); ++i)
    {
        if (n % i == 0)
        {
            isprime_ = false;
            break;
        }
    }

    return isprime_;
}

int main()
{
    for (int i{0}; i < 20; ++i)
        println(i, " is ", isprime(i) ? "" : "not ", "prime");

    return 0;
}
