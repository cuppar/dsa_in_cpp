#include <cstddef>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>

#include "Timer.h"
#include "Random.h"

template<typename T>
T& topK1(std::vector<T>& vec, const int k)
{
    std::sort(vec.begin(), vec.end(), std::greater());
    return vec[k - 1];
}

template<typename T>
T& topK2(std::vector<T>& vec, const int k)
{
    std::vector<std::reference_wrapper<T>> topK;

    for (int i{0}; i < k; ++i)
        topK.push_back(vec[i]);

    std::sort(topK.begin(), topK.end(), std::greater<T> {});

    for (int cur{k}; cur < static_cast<int>(vec.size()); ++cur)
        if (vec[cur] > topK[k - 1])
        {
            int smaller{0};

            while (topK[smaller] >= vec[cur])
                ++smaller;

            for (int j{k - 1}; j >= smaller; --j)
                topK[j + 1] = topK[j];

            topK[smaller] = vec[cur];
        }

    return topK[k - 1];
}

using topKFn = std::function<int& (std::vector<int>&, const int)>;
// test a top k function, return the runtime of ms
long testTime(topKFn fn, int size, int count)
{
    std::vector<int> vec;
    vec.reserve(size);

    for (int i{0}; i < size; ++i)
        vec.push_back(Random::get(1, size));

    int result;

    Timer t;

    for (int i{0}; i < count; ++i)
        result = fn(vec, static_cast<int>(vec.size()) / 2);

    return t.elapsed();
}

int main()
{
    const int count = 2;
    std::cout << std::setprecision(10) << std::left;
    std::cout <<"size\ttopK1\ttopK2\n";

    for (int size{2}; size <= 100000; size *= 2)
    {
        auto t1{testTime(&topK1<int>, size, count)};
        auto t2{testTime(&topK2<int>, size, count)};
        std::cout << size << "\t" << t1 << "\t" << t2 << "\n";
    }

    return 0;
}
