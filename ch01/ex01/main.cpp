#include <cstddef>
#include <functional>
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

    for (int cur{k}; cur < vec.size(); ++cur)
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



int main()
{
    const int SIZE = 100000;
    const int TEST_COUNT = 1000;
    std::vector<int> vec;
    vec.reserve(SIZE);

    for (int i{0}; i < SIZE; ++i)
        vec.push_back(Random::get(1, SIZE));

    int result1;

    Timer t1;

    for (int i{0}; i < TEST_COUNT; ++i)
        result1 = topK1(vec, static_cast<int>(vec.size()) / 2);

    t1.elapsed();

    std::cout << "topK1: " << result1 << '\n';

    int result2;

    Timer t2;

    for (int i{0}; i < TEST_COUNT; ++i)
        result2 = topK2(vec, static_cast<int>(vec.size()) / 2);

    t2.elapsed();

    std::cout << "topK2: " << result2 << '\n';

    return 0;
}
