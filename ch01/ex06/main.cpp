#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

void permute(std::string& str, int low, int high)
{
    if (low == high)
        std::cout << str << '\n';

    else
        for (int i{low}; i <= high; ++i)
        {
            std::swap(str[low], str[i]);
            permute(str, low + 1, high);
            std::swap(str[low], str[i]);
        }
}

void permute(std::string& str)
{
    permute(str, 0, str.length() - 1);
}

int main()
{
    std::string str{"abcd"};
    permute(str);
    return 0;
}
