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

int gcb(int a, int b)
{
    if (a < b)
        return gcb(b, a);

    if (b == 0)
        return a;

    if (a % 2 == 0 && b % 2 == 0)
        return 2 * gcb(a / 2, b / 2);
    if (a % 2 == 0 && b % 2 != 0)
        return gcb(a / 2, b);
    if (a % 2 != 0 && b % 2 == 0)
        return gcb(a, b / 2);
    if (a % 2 != 0 && b % 2 != 0)
        return gcb((a + b) / 2, (a - b) / 2);
}

int main()
{
    std::cout << gcb(5, 15) << '\n';
    std::cout << gcb(6, 15) << '\n';
    std::cout << gcb(9, 15) << '\n';
    std::cout << gcb(8, 24) << '\n';
    return 0;
}
