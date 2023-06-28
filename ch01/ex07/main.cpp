#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename T>
class Collection final
{
public:
    Collection()
    {
        std::cout << "default constractor\n";
    }
    Collection(int size)
    {
        std::cout << "constractor(int size): size = " << size << "\n";

        if (size < 0)
            throw std::runtime_error("Collection size need non-negative");

        if (size > 0)
            resize(size);
    }
    Collection(std::initializer_list<T> list)
        : Collection(list.size())
    {
        std::cout << "initializer_list constructor" << "\n";
        int i{0};

        for (auto el : list)
        {
            m_array[i] = el;
            ++i;
        }
    }
    Collection& operator=(std::initializer_list<T> list)
    {
        std::cout << "initializer_list assignment" << "\n";
        resize(list.size());
        int i{0};

        for (auto el : list)
        {
            (*this)[i] = el + 10;
            ++i;
        }

        return *this;
    }
    // big five
    friend void swap(Collection& a, Collection& b)
    {
        using std::swap;
        swap(a.m_size, b.m_size);
        swap(a.m_array, b.m_array);
    }
    ~Collection()
    {
        std::cout << "destractor\n";
        delete[] m_array;
    }
    Collection(const Collection& c)
        : Collection(c.m_size)
    {
        for (int i{0}; i < c.m_size; ++i)
            m_array[i] = c.m_array[i];
    }
    Collection(Collection&& c)
        : Collection()
    {
        swap(*this, c);
    }
    Collection& operator=(const Collection& c)
    {
        Collection other{c};
        swap(*this, other);
        return *this;
    }
    Collection& operator=(Collection&& other)
    {
        if (this == &other)
            return *this;

        swap(*this, other);
        return *this;
    }
    // Collection& operator=(const Collection& c)
    // {
    // if (this == &c)
    // return *this;
    //
    // T* new_array = new T[c.m_size] {};
    //
    // for (int i{0}; i < c.m_size; ++i)
    // new_array[i] = c.m_array[i];
    //
    // delete[] m_array;
    //
    // m_array = new_array;
    //
    // m_size = c.m_size;
    //
    // return *this;
    // }
    // Collection& operator=(Collection&& c)
    // {
    // if (this == &c)
    // return *this;
    //
    // delete[] m_array;
    // m_array = c.m_array;
    // m_size = c.m_size;
    // c.m_array = nullptr;
    // c.m_size = 0;
    // return *this;
    // }
    // end big five
    void makeEmpty()
    {
        delete[] m_array;
        m_array = nullptr;
        m_size = 0;
    }
    bool isEmpty()
    {
        return m_size == 0;
    }
    void print(std::ostream& out) const
    {
        for (int i{0}; i < m_size; ++i)
            out << m_array[i] << ' ';
    }
    const T& operator[](int index)const
    {
        return m_array[index];
    }
    T& operator[](int index)
    {
        return m_array[index];
    }

private:
    T* m_array{nullptr};
    int m_size{0};
public:
    void resize(int size)
    {
        std::cout << "resize to " << size << '\n';

        if (size < 0)
            return;

        if (size == 0)
        {
            makeEmpty();
            return;
        }

        T* new_array = new T[size] {};

        if (m_array && m_size > 0)
        {
            int move_size = size > m_size ? m_size : size;

            for (int i{0}; i < move_size; ++i)
                new_array[i] = m_array[i];

            delete[] m_array;
        }

        m_size = size;
        m_array = new_array;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out,
                         const Collection<T>& collection)
{
    collection.print(out);
    return out;
}

void printline()
{
    std::cout << "\n##################################\n";
}

int main()
{
    Collection<int> collection{1, 2, 3, 4, 5, 6};
    std::cout << collection << '\n';
    collection.resize(10);
    std::cout << collection << '\n';
    collection.resize(3);
    std::cout << collection << '\n';
    printline();
    Collection<int> c2;
    // c2 = std::move(collection);
    c2 = collection;
    c2[0] = 9;
    std::cout << "c2[0]: " << c2[0] << '\n';
    std::cout << "collection[0]: " << collection[0] << '\n';
    std::cout << collection << '\n';
    printline();
    Collection<int> c3;
    c3 = {9, 8, 7, 6, 5};
    c3[0] = 55;
    std::cout << "c3: " << c3 << '\n';
    std::cout << "c3[0]: " << c3[0] << '\n';
    return 0;
}
