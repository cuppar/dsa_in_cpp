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

    class const_iterator
    {
    public:
        const_iterator()
            : current{nullptr},
              invalidated{true},
              theVector{Vector<int>{}},
              initArray{nullptr}
        {
        }

        const Object &operator*() const
        {
            if (isInvalidated())
                throw std::runtime_error("invalidated iterator");
            return *current;
        }

        const_iterator &operator++()
        {
            if (current == theVector->end().current)
                throw std::runtime_error("iterator out of range");
            ++current;
            return *this;
        }
        const_iterator operator++(int)
        {
            if (current == theVector->end().current)
                throw std::runtime_error("iterator out of range");
            const_iterator old{*this};
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }
        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        Object *current;
        bool invalidated;
        const Vector<Object> *theVector;
        Object *initArray;

        const_iterator(const Vector &v, Object *p)
            : current{p},
              invalidated{false},
              theVector{&v},
              initArray{theVector->theArray}
        {
        }

        bool isInvalidated() const
        {
            return invalidated || initArray != theVector->theArray;
        }
        void invalidate() { invalidated = true; }

        friend class Vector<Object>;
    };
    class iterator : public const_iterator
    {
    public:
        const Object &operator*() const
        {
            if (this->isInvalidated())
                throw std::runtime_error("invalidated iterator");
            return *this->current;
        }

        Object &operator*()
        {
            if (this->isInvalidated())
                throw std::runtime_error("invalidated iterator");
            return *this->current;
        }

        iterator &operator++()
        {
            if (this->current == this->theVector->end().current)
                throw std::runtime_error("iterator out of range");
            ++this->current;
            return *this;
        }
        iterator operator++(int)
        {
            if (this->current == this->theVector->end().current)
                throw std::runtime_error("iterator out of range");
            auto old{*this};
            ++(*this);
            return old;
        }

    protected:
        iterator(const Vector &v, Object *p)
            : const_iterator(v, p)
        {
        }
        friend class Vector<Object>;
    };

    iterator insert(const_iterator &pos, const Object &x)
    {
        if (pos.theVector != this)
            throw std::runtime_error("mismatch iterator");
        int offset{0};
        auto it{begin()};
        while (it != pos)
        {
            ++offset;
            ++it;
        }
        if (theSize == theCapacity)
        {
            theCapacity = theCapacity * 2 + 1;
            auto newArray = new Object[theCapacity];
            for (int i{0}; i < offset; ++i)
                newArray[i] = std::move(theArray[i]);
            newArray[offset] = x;
            for (int i{offset}; i < theSize; ++i)
                newArray[i + 1] = theArray[i];

            std::swap(theArray, newArray);
            delete[] newArray;
            pos.invalidate();
        }
        else
        {
            for (int i{theSize - 1}; i >= offset; --i)
                theArray[i + 1] = theArray[i];
            theArray[offset] = x;
        }
        ++theSize;

        auto new_it{begin()};
        for (int i{0}; i < offset; ++i)
            ++new_it;
        return new_it;
    }

    iterator erase(const_iterator &pos)
    {
        if (pos.theVector != this)
            throw std::runtime_error("mismatch iterator");
        int offset{0};
        auto it{begin()};
        while (it != pos)
        {
            ++it;
            ++offset;
        }

        if (theSize == theCapacity / 2)
        {
            theCapacity /= 2;
            auto newArray = new Object[theCapacity];
            for (int i{0}; i < offset; ++i)
                newArray[i] = theArray[i];
            for (int i{offset}; i < theSize - 1; ++i)
                newArray[i] = theArray[i + 1];
            std::swap(theArray, newArray);
            delete[] newArray;
            pos.invalidate();
        }
        else
        {
            for (int i{offset}; i < theSize - 1; ++i)
                theArray[i] = theArray[i + 1];
        }
        --theSize;

        auto new_it{begin()};
        for (int i{0}; i < offset; ++i)
            ++new_it;
        return new_it;
    }

    iterator begin()
    {
        return {*this, &theArray[0]};
    }
    const_iterator begin() const
    {
        return {*this, &theArray[0]};
    }
    iterator end()
    {
        return {*this, &theArray[size()]};
    }
    const_iterator end() const
    {
        return {*this, &theArray[size()]};
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

    // println("######### push_back");
    // v1.reserve(5);
    // println(v1);
    // println("size: ", v1.size());
    // println("capacity: ", v1.capacity());
    // auto pos{v1.begin()};
    // for (int i{0}; i < 3; ++i)
    //     ++pos;
    // println("before push: *pos: ", *pos);
    // v1.push_back(9);
    // println("after push: *pos: ", *pos);
    // println(v1);
    // println("size: ", v1.size());
    // println("capacity: ", v1.capacity());
    println("######### insert");
    v1.reserve(5);
    println(v1);
    println("size: ", v1.size());
    println("capacity: ", v1.capacity());
    auto insert_pos{v1.begin()};
    for (int i{0}; i < 32; ++i)
        ++insert_pos;
    println("before insert: *insert_pos: ", *insert_pos);

    auto it = v1.insert(insert_pos, 9);
    println(v1);
    // println("after insert: *insert_pos: ", *insert_pos);
    println("size: ", v1.size());
    println("capacity: ", v1.capacity());
    println("inserted: ", *it);
    // println("######### erase");
    // v1.reserve(11);
    // println(v1);
    // println("size: ", v1.size());
    // println("capacity: ", v1.capacity());
    // auto erase_pos{v1.begin()};
    // for (int i{0}; i < 4; ++i)
    //     ++erase_pos;
    // auto it = v1.erase(erase_pos);
    // println(v1);
    // println("size: ", v1.size());
    // println("capacity: ", v1.capacity());
    // println("it == v1.end(): ", it == v1.end());
}

int main()
{
    exec();
    return 0;
}
