#include <iostream>

void pa(int n)
{
    std::cout << n;
}

void p(int n)
{
    if (n >= 10)
        p(n / 10);

    pa(n % 10);
}

int main()
{
    int n{12345};
    p(n);
    return 0;
}
