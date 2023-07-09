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

using Arr = std::vector<int>;

// int find_Ai_eq_i(Arr arr, int l, int r)
// {
//     if (l > r)
//         return -1;
//     int mid = (l + r) / 2;
//     if (arr[mid] > mid + 1)
//         return find_Ai_eq_i(arr, l, mid - 1);
//     else if (arr[mid] < mid + 1)
//         return find_Ai_eq_i(arr, mid + 1, r);
//     else
//         return mid + 1;
// }

int find_Ai_eq_i(Arr arr, int l, int r)
{
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (arr[mid] > mid + 1)
            r = mid - 1;
        else if (arr[mid] < mid + 1)
            l = mid + 1;
        else
            return mid + 1;
    }
    return -1;
}

int find_Ai_eq_i(Arr arr)
{
    return find_Ai_eq_i(arr, 0, arr.size() - 1);
}

int main()
{
    Arr arr1{4, 6, 2, 3, 8};
    Arr arr2{4, 6, 1, -1};
    Arr arr3{4, 6, -1, 2};
    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());
    std::sort(arr3.begin(), arr3.end());
    int r1{find_Ai_eq_i(arr1)};
    int r2{find_Ai_eq_i(arr2)};
    int r3{find_Ai_eq_i(arr3)};
    std::cout << r1 << '\n';
    std::cout << r2 << '\n';
    std::cout << r3 << '\n';
    return 0;
}
