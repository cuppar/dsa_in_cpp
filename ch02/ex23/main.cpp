#include <iostream>
#include "util.h"

int pow(int x, int e)
{
    int acc{1};
    int base {x};
    int exp{e};

    while (exp != 1)
    {
        if (exp % 2 == 1)
            acc *= base;

        base *= base;
        exp /= 2;
    }

    return acc * base;
}

void exec()
{
    println(pow(3, 4));
}

int main()
{
    exec();
    return 0;
}
