#include <iostream>
#include <ostream>
#include <vector>

template<typename T, typename C>
const T& findMax(const std::vector<T>& arr, C less)
{
    int max{0};

    for (int i{1}; i < static_cast<int>(arr.size()); ++i)
        if (less(arr[max], arr[i]))
            max = i;

    return arr[max];
}

template<typename T>
const T& findMax(const std::vector<T>& arr)
{
    return findMax(arr, std::less<T> {});
}

template<typename C>
class Compare
{
public:
    bool operator()(const C& first, const C& second)
    {
        return first < second;
    }
};

class Rect
{
public:
    Rect(int width, int height)
        : m_width{width}, m_height{height}
    {
    }
    int getWidth() const
    {
        return m_width;
    }
    int getHeight() const
    {
        return m_height;
    }
    int getArea() const
    {
        return getWidth() * getHeight();
    }
    int getPerimeter() const
    {
        return 2 * (getWidth() + getHeight());
    }
    // less
    bool operator<(const Rect& other) const
    {
        // return getArea() < other.getArea();
        return getPerimeter() < other.getPerimeter();
    }
private:
    int m_width;
    int m_height;
};

std::ostream& operator<< (std::ostream& out, const Rect& r)
{
    return out << "Rect(" << r.getWidth() << ", " << r.getHeight() << ")";
}

int main()
{
    std::vector<Rect> v
    {
        Rect{4, 5},
        Rect{2, 15},
        Rect{7, 5},
        Rect{3, 5},
    };
    std::cout << "findMax: " << findMax(v, Compare<Rect> {}) << '\n';
    return 0;
}
