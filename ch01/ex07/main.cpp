#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename T>
class Collection final
{
public:
    Collection()
        : m_array{nullptr}, m_size{0}, m_capacity{0}
    {
        std::cout << "default constractor\n";
    }
    Collection(int size)
        : Collection()
    {
        std::cout << "constractor(int size): size = " << size << "\n";

        if (size < 0)
            throw std::runtime_error("Collection size need non-negative");

        if (size > 0)
            reserve(size);
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
        swap(a.m_capacity, b.m_capacity);
        swap(a.m_array, b.m_array);
    }
    ~Collection()
    {
        std::cout << "destractor\n";
        delete[] m_array;
    }
    Collection(const Collection& c)
        : Collection(c.m_capacity)
    {
        for (int i{0}; i < c.m_size; ++i)
            m_array[i] = c.m_array[i];

        m_size = c.m_size;
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

        out << " (size: " << m_size << ", capacity: " << m_capacity << ")";
    }
    const T& operator[](int index)const
    {
        if (index >= m_size || index < 0)
            throw std::runtime_error("out of range");

        return m_array[index];
    }
    T& operator[](int index)
    {
        if (index >= m_size || index < 0)
            throw std::runtime_error("out of range");

        return m_array[index];
    }
    void reserve(int size)
    {
        if (m_capacity < size)
        {
            m_capacity = size;

            if (m_array)
            {
                T* new_array = new T[m_capacity] {};

                for (int i{0}; i < m_size; ++i)
                    new_array[i] = m_array[i];

                delete[] m_array;

                m_array = new_array;
            }

            else
            {
                m_array = new T[m_capacity] {};
                m_size = m_capacity;
            }
        }
    }

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

        if (size > m_capacity)
        {
            if (m_capacity <= 0)
                m_capacity = 1;

            // double capacity
            while (m_capacity < size)
                m_capacity *= 2;

            T* new_array = new T[m_capacity] {};

            for (int i{0}; i < m_size; ++i)
                new_array[i] = m_array[i];

            delete[] m_array;

            m_array = new_array;

            m_size = size;
        }

        else
        {
            // just change size
            int old_size = m_size;
            m_size = size;

            if (old_size < size)
            {
                // init the more el
                for (int i{old_size}; i < size; ++i)
                    m_array[i] = T{};
            }
        }
    }

    void insert(T obj, int pos)
    {
        if (pos < 0 || pos > m_size)
            throw std::runtime_error("insert pos out of range");

        resize(m_size + 1);

        for (int i{m_size - 1}; i >= pos; --i)
            m_array[i + 1] = m_array[i];

        m_array[pos] = obj;
    }
    void remove(int pos)
    {
        if (pos < 0 || pos >= m_size)
            throw std::runtime_error("remove pos out of range");

        for (int i{pos + 1}; i < m_size; ++i)
            m_array[i - 1] = m_array[i];

        m_size--;
    }
    bool contains(T obj)
    {
        for (int i{0}; i < m_size; ++i)
        {
            if (obj == m_array[i])
                return true;
        }

        return false;
    }
private:
    T* m_array;
    int m_size;
    int m_capacity;
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
    std::cout << "collection: " << collection << '\n';
    std::cout << "c2: " << c2 << '\n';
    printline();
    Collection<int> c3;
    c3 = {9, 8, 7, 6, 5};
    c3[0] = 55;
    std::cout << "c3: " << c3 << '\n';
    std::cout << "c3[0]: " << c3[0] << '\n';
    printline();
    Collection<int> c4(10);
    std::cout << "c4: " << c4 << '\n';
    c4.resize(5);
    std::cout << "resize(5): " << '\n';
    std::cout << "c4: " << c4 << '\n';
    c4.makeEmpty();
    std::cout << "makeEmpty(): " << '\n';
    std::cout << "c4: " << c4 << '\n';
    printline();
    Collection<int> c5;
    std::cout << "c5: " << c5 << '\n';
    c5.resize(3);
    std::cout << "resize(3): " << '\n';
    std::cout << "c5: " << c5 << '\n';
    c5.resize(5);
    std::cout << "resize(5): " << '\n';
    std::cout << "c5: " << c5 << '\n';
    c5.reserve(3);
    std::cout << "reserve(3): " << '\n';
    std::cout << "c5: " << c5 << '\n';
    c5.makeEmpty();
    std::cout << "makeEmpty(): " << '\n';
    std::cout << "c5: " << c5 << '\n';
    c5.reserve(13);
    std::cout << "reserve(13): " << '\n';
    std::cout << "c5: " << c5 << '\n';
    printline();
    Collection<int> c6;
    std::cout << "c6: " << c6 << '\n';

    for (int i{0}; i < 10; ++i)
    {
        c6.insert(i, i);
        std::cout << "c6: " << c6 << '\n';
    }

    c6.remove(4);
    std::cout << "c6: " << c6 << '\n';
    c6.remove(0);
    std::cout << "c6: " << c6 << '\n';
    c6.remove(6);
    std::cout << "c6: " << c6 << '\n';
    std::cout << "contains 6: " << c6.contains(6) << '\n';
    std::cout << "contains 8: " << c6.contains(8) << '\n';
    return 0;
}
