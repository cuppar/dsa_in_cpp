#include <iostream>

// return numbers of '1' of binary representation of n, n>=0
int f(int n)
{
    if (n < 2)
        return n;

    else if (n % 2 == 1)
        return f(n / 2) + 1;

    else
        return f(n / 2);
}

void pf(int n)
{
    if (n < 2)
        std::cout << n;

    else
    {
        pf(n / 2);
        std::cout << (n % 2 == 0 ? '0' : '1');
    }
}

int main()
{
    for (int i{0}; i < 50; ++i)
    {
        std::cout << "numbers of '1' of " << i << "(";
        pf(i);
        std::cout << "): " << f(i) << '\n';
    }

    return 0;
}
