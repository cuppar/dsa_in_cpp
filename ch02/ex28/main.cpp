#include <algorithm>
#include <iostream>
#include <vector>
#include "util.h"

using Arr = std::vector<int>;
int max_j_sub_i_1(Arr arr)
{
    int max{0};
    int mmin{arr[0]};

    for (int i{0}; i < (int)arr.size(); ++i)
    {
        mmin = std::min({mmin, arr[i]});
        max = std::max({max, arr[i] - mmin});
    }

    return max;
}

int max_j_sub_i_2(Arr arr)
{
    int max{0};
    int mmax{arr[arr.size() - 1]};

    for (int i{(int)arr.size() - 1}; i >= 0; --i)
    {
        mmax = std::max({mmax, arr[i]});
        max = std::max({max, mmax - arr[i]});
    }

    return max;
}
int max_j_div_i_1(Arr arr)
{
    int max{0};
    int mmin{arr[0]};

    for (int i{0}; i < (int)arr.size(); ++i)
    {
        mmin = std::min({mmin, arr[i]});
        max = std::max({max, arr[i] / mmin});
    }

    return max;
}
int max_j_div_i_2(Arr arr)
{
    int max{0};
    int mmax{arr[arr.size() - 1]};

    for (int i{(int)arr.size() - 1}; i >= 0; --i)
    {
        mmax = std::max({mmax, arr[i]});
        max = std::max({max, mmax / arr[i]});
    }

    return max;
}

void exec()
{
    Arr arr{3, 5, 2, 5, 8, 3, 2, 7};
    println(max_j_sub_i_1(arr));
    println(max_j_sub_i_2(arr));
    println(max_j_div_i_1(arr));
    println(max_j_div_i_2(arr));
}

int main()
{
    exec();
    return 0;
}
