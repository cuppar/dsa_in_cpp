#include <algorithm>
#include <iostream>
#include <vector>
#include "util.h"

using Arr = std::vector<int>;
int find_majority_candidate(Arr arr, int size)
{
    if (size == 0)
        return -1;

    if (size == 1)
        return arr[0];

    int new_size{0};

    for (int i{0}; i < size; i += 2)
    {
        if (i + 1 < size)
        {
            if (arr[i] == arr[i + 1])
                arr[new_size++] = arr[i];
        }
    }

    if (size / 2 * 2 < size)
        arr[new_size++] = arr[size - 1];

    return find_majority_candidate(arr, new_size);
}

int find_majority(Arr arr)
{
    Arr copy{arr};
    int candidate{find_majority_candidate(copy, copy.size())};

    if (candidate == -1)
        return -1;

    if (std::count(arr.begin(), arr.end(), candidate)
            > (int)arr.size() / 2)
        return candidate;

    else
        return -1;
}

void exec()
{
    Arr arr{1, 3, 2, 3, 3};
    println(find_majority(arr));
}

int main()
{
    exec();
    return 0;
}
