#include "util.h"
#include <cmath>
#include <functional>
#include <iostream>

using Fn = std::function<double(double)>;
double solve1(Fn f, double low,
              double high)
{
    double pic{0.000001};

    while (low < high)
    {
        double mid{(low + high) / 2.0};
        double diff{std::abs(f(mid))};

        if (diff < pic)
            return mid;

        else if (f(mid) > 0)
            high = mid;

        else
            low = mid;
    }

    return -1;
}

double solve2(Fn f, double low,
              double high)
{
    double pic{0.000001};
    double mid{(low + high) / 2.0};
    double diff{std::abs(f(mid))};

    if (diff < pic)
        return mid;

    else if (f(mid) > 0)
        return solve2(f, low, mid);

    else
        return solve2(f, mid, high);
}

double f(double x)
{
    return x * x - 100;
}

void exec(Fn f, double low, double high)
{
    util::println("solve1: f(x) = 0 in range(", low, ", ", high,
                  "): x = ",
                  solve1(f, low, high));
    util::println("solve2: f(x) = 0 in range(", low, ", ", high,
                  "): x = ",
                  solve2(f, low, high));
}

int main()
{
    exec(f, -20, 0);
    exec(f, 0, 20);
    return 0;
}
