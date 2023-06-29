#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v(10);
    std::cout << v.size() << '\n';
    std::cout << v.capacity() << '\n';
    std::cout << v.empty() << '\n';
    v.resize(5);
    std::cout << "v.resize(5): " << '\n';
    std::cout << v.size() << '\n';
    std::cout << v.capacity() << '\n';
    std::cout << v.empty() << '\n';
    v.clear();
    std::cout << "v.clear(): " << '\n';
    std::cout << v.size() << '\n';
    std::cout << v.capacity() << '\n';
    std::cout << v.empty() << '\n';
    std::vector<int> v2;
    v2.resize(3);
    std::cout << "v2: " << '\n';
    std::cout << v2.size() << '\n';
    std::cout << v2.capacity() << '\n';
    std::cout << v2.empty() << '\n';
    v2.resize(5);
    std::cout << "v2.resize(5): " << '\n';
    std::cout << v2.size() << '\n';
    std::cout << v2.capacity() << '\n';
    std::cout << v2.empty() << '\n';
    v2.reserve(3);
    std::cout << "v2.reserve(3) " << '\n';
    std::cout << v2.size() << '\n';
    std::cout << v2.capacity() << '\n';
    std::cout << v2.empty() << '\n';
    v2.clear();
    std::cout << "v2.clear(): " << '\n';
    std::cout << v2.size() << '\n';
    std::cout << v2.capacity() << '\n';
    std::cout << v2.empty() << '\n';
    v2.reserve(13);
    std::cout << "v2.reserve(13) " << '\n';
    std::cout << v2.size() << '\n';
    std::cout << v2.capacity() << '\n';
    std::cout << v2.empty() << '\n';
    return 0;
}
