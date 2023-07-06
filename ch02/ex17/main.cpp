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

using Arr = std::vector<int>;

int min_sub_sum(const Arr &arr)
{
    int min_sub_sum{0};
    int this_sub_sum{0};
    for (size_t i{0}; i < arr.size(); ++i)
    {
        this_sub_sum += arr[i];
        if (this_sub_sum < min_sub_sum)
            min_sub_sum = this_sub_sum;
        else if (this_sub_sum > 0)
            this_sub_sum = 0;
    }
    return min_sub_sum;
}

int min_pos_sub_sum(const Arr &arr, int l, int r)
{
    // for empty array
    if (l > r)
        return 0;
    if (l == r)
        return arr[l] > 0 ? arr[l] : 0;
    int mid{(l + r) / 2};
    int left_sum{min_pos_sub_sum(arr, l, mid)};
    int right_sum{min_pos_sub_sum(arr, mid + 1, r)};

    std::vector<int> left_border_sums;
    int left_this_sum{0};
    for (int i{mid}; i >= l; --i)
    {
        left_this_sum += arr[i];
        left_border_sums.push_back(left_this_sum);
    }
    std::sort(left_border_sums.begin(), left_border_sums.end());

    std::vector<int> right_border_sums;
    int right_this_sum{0};
    for (int i{mid + 1}; i <= r; ++i)
    {
        right_this_sum += arr[i];
        right_border_sums.push_back(right_this_sum);
    }
    std::sort(right_border_sums.begin(), right_border_sums.end());

    int i{0};
    int j{static_cast<int>(right_border_sums.size()) - 1};
    int min_mid_sum{0};
    while (i < left_border_sums.size() && j >= 0)
    {
        int sum{left_border_sums[i] + right_border_sums[j]};
        if (sum <= 0)
            ++i;
        else
        {
            --j;
            // only init min_mid_sum
            if (min_mid_sum <= 0)
                min_mid_sum = sum;

            if (sum < min_mid_sum)
                min_mid_sum = sum;
        }
    }

    int result{std::max({left_sum, right_sum, min_mid_sum})};

    if (left_sum > 0 && left_sum < result)
        result = left_sum;
    if (right_sum > 0 && right_sum < result)
        result = right_sum;
    if (min_mid_sum > 0 && min_mid_sum < result)
        result = min_mid_sum;

    return result;
}

int min_pos_sub_sum(const Arr &arr)
{
    return min_pos_sub_sum(arr, 0, static_cast<int>(arr.size()) - 1);
}

int min_pos_sub_sum2(const Arr &arr)
{
    int min_sum{0};
    for (int i{0}; i < arr.size(); ++i)
    {
        int this_sum{0};
        for (int j{i}; j < arr.size(); ++j)
        {
            this_sum += arr[j];
            if (this_sum > 0 && min_sum <= 0)
                min_sum = this_sum;
            if (this_sum > 0 && this_sum < min_sum)
                min_sum = this_sum;
        }
    }
    return min_sum;
}

int max_sub_pro(const Arr &arr)
{
    int max_pro{arr[0]};
    int this_max_pro{arr[0]};
    int this_min_pro{arr[0]};

    for (int i{1}; i < arr.size(); ++i)
    {
        int temp = this_max_pro;
        this_max_pro = std::max({arr[i] * this_max_pro,
                                 arr[i] * this_min_pro,
                                 arr[i]});
        this_min_pro = std::min({arr[i] * temp,
                                 arr[i] * this_min_pro,
                                 arr[i]});
        if (this_max_pro > max_pro)
            max_pro = this_max_pro;
    }
    return max_pro;
}

int main()
{
    Arr arr{-2, 3, 5, -6, -1, 2};
    std::cout << min_sub_sum(arr) << '\n';
    std::cout << min_pos_sub_sum(arr) << '\n';
    std::cout << min_pos_sub_sum2(arr) << '\n';
    std::cout << max_sub_pro(arr) << '\n';
    return 0;
}
