#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
T& topK1(std::vector<T>& vec, const int k)
{
    std::sort(vec.begin(), vec.end(), std::greater());
    return vec[k - 1];
}

int main()
{
    std::vector vec{8, 100, 342, 3, 5, 24};
    //int result{topK1(vec, static_cast<int>(vec.size()) / 2)};
    int result{topK1(vec, 1)};
    std::cout << "selected: " << result << '\n';
    return 0;
}
