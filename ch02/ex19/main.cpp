#include "util.h"
#include <iostream>
#include <ostream>
#include <vector>

struct Result
{
    int sum;
    int left;
    int right;
};
bool operator<(const Result& a, const Result& b)
{
    return a.sum < b.sum;
}
std::ostream& operator<<(std::ostream& out, const Result& r)
{
    return out << "Result{" << r.sum << ", " << r.left << ", " << r.right
           << "}";
}

using Arr = std::vector<int>;

Result mss(Arr arr, int low, int high)
{
    // for empty arr
    if (low > high)
        return Result{-1, -1, -1};

    if (low == high)
        return Result{arr[low], low, high};

    int mid{(low + high) / 2};

    Result left_result = mss(arr, low, mid);

    Result right_result = mss(arr, mid + 1, high);

    Result mid_result;

    int max_left_border_sum{0};

    int this_left_border_sum{0};

    for (int i{mid}; i >= low; --i)
    {
        this_left_border_sum += arr[i];

        if (this_left_border_sum > max_left_border_sum)
        {
            max_left_border_sum = this_left_border_sum;
            mid_result.left = i;
        }
    }

    int max_right_border_sum{0};
    int this_right_border_sum{0};

    for (int i{mid + 1}; i <= high; ++i)
    {
        this_right_border_sum += arr[i];

        if (this_right_border_sum > max_right_border_sum)
        {
            max_right_border_sum = this_right_border_sum;
            mid_result.right = i;
        }
    }

    mid_result.sum = max_left_border_sum + max_right_border_sum;
    Result max_result;

    if (left_result < right_result)
        max_result = right_result;

    else
        max_result = left_result;

    if (max_result < mid_result)
        max_result = mid_result;

    return max_result;
}

Result mss(Arr arr)
{
    return mss(arr, 0, arr.size() - 1);
}

void exec()
{
    Arr v{-1, 2, -3, 4, -6, 4, 5, -2, 3};
    Result r{mss(v)};
    println(v);
    println(r);
}

int main()
{
    exec();
    return 0;
}
