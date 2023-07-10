#include <iostream>
#include <algorithm>
#include "util.h"

static const int SPARE_CAPACITY = 16;

template <typename Object>
class Vector
{
public:
    explicit Vector(int initSize = 0)
        : theSize{initSize},
          theCapacity{initSize + SPARE_CAPACITY}
    {
        theArray = new Object[theCapacity];
    }

    // init list constr
    Vector(std::initializer_list<Object> list)
        : Vector(list.size())
    {
        int i{0};
        for (auto &el : list)
        {
            theArray[i] = el;
            ++i;
        }
    }
    Vector &operator=(std::initializer_list<Object> list)
    {
        auto copy{list};
        swap(*this, copy);
        return *this;
    }

    // big five
    ~Vector()
    {
        delete[] theArray;
    }
    Vector(const Vector &rhs)
        : theCapacity{rhs.theCapacity},
          theSize{rhs.theSize},
          theArray{nullptr}
    {
        theArray = new Object[theCapacity];
        for (int i{0}; i < theSize; ++i)
            theArray[i] = rhs.theArray[i];
    }
    Vector(Vector &&rhs)
        : theCapacity{rhs.theCapacity},
          theSize{rhs.theSize},
          theArray{rhs.theArray}
    {
        rhs.theArray = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }
    friend inline void swap(Vector &a, Vector &b)
    {
        std::swap(a.theArray, b.theArray);
        std::swap(a.theSize, b.theSize);
        std::swap(a.theCapacity, b.theCapacity);
    }
    Vector &operator=(const Vector &rhs)
    {
        auto copy{rhs};
        swap(*this, copy);
        return *this;
    }
    Vector &operator=(Vector &&rhs)
    {
        swap(*this, rhs);
        return *this;
    }

    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
    }
    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;
        auto newArray = new Object[newCapacity];
        for (int i{0}; i < theSize; ++i)
            newArray[i] = std::move(theArray[i]);
        theCapacity = newCapacity;
        std::swap(theArray, newArray);
        delete[] newArray;
    }

    Object &operator[](int index)
    {
        if (index < 0 || index >= theSize)
            throw std::runtime_error("Vector index out of range");
        return theArray[index];
    }
    const Object &operator[](int index) const
    {
        if (index < 0 || index >= theSize)
            throw std::runtime_error("Vector index out of range");
        return theArray[index];
    }

    int size() const { return theSize; }
    int capacity() const { return theCapacity; }
    bool empty() const { return theSize == 0; }
    void clear()
    {
        while (!empty())
        {
            pop_back();
        }
    }

    void push_back(const Object &x)
    {
        if (theSize == theCapacity)
            reserve(theCapacity * 2 + 1);
        theArray[theSize++] = x;
    }
    void push_back(Object &&x)
    {
        if (theSize == theCapacity)
            reserve(theCapacity * 2 + 1);
        theArray[theSize++] = std::move(x);
    }
    void pop_back()
    {
        if (theSize == theCapacity / 2)
            reserve(theCapacity / 2);
        --theSize;
    }
    const Object &back() const
    {
        return theArray[theSize - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin()
    {
        return &theArray[0];
    }
    const_iterator begin() const
    {
        return &theArray[0];
    }
    iterator end()
    {
        return &theArray[size()];
    }
    const_iterator end() const
    {
        return &theArray[size()];
    }

private:
    Object *theArray;
    int theSize;
    int theCapacity;
};

template <typename Object>
std::ostream &operator<<(std::ostream &os, const Vector<Object> &v)
{
    const char *sp[] = {"", ", "};
    int i{0};
    os << "{ ";
    for (auto &el : v)
    {
        os << sp[i] << el;
        i = 1;
    }
    return os << " }";
}

void exec()
{
    Vector<int> v1 = {1, 2, 3};
    Vector<int> v2 = {4, 5, 6, 7, 8};
    println(v1);
    println(v2);
    v1 = std::move(v2);
    // v1 = v2;
    println(v1);
    println(v2);

    auto found = std::find(v1.begin(), v1.end(), 6);
    println("size: ", v1.size());
    println("capacity: ", v1.capacity());
    println(found);
    println(v1.end());
    if (found != v1.end())
    {
        println("found: ", *found);
    }
}

int main()
{
    exec();
    return 0;
}
