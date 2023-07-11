#include <iostream>
#include <algorithm>
#include <list>
#include "util.h"

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node *prev;
        Node *next;

        Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
            : data{d}, prev{p}, next{n} {}
        Node(T &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator
    {
    public:
        const_iterator()
            : current{nullptr},
              theList{nullptr}
        {
        }

        const T &operator*() const
        {

            return retrieve();
        }

        const_iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++(int)
        {
            auto old{*this};
            ++(*this);
            return old;
        }
        const_iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator--(int)
        {
            auto old{*this};
            --(*this);
            return old;
        }

        const_iterator operator+(int k) const
        {
            auto it{*this};
            for (int i{0}; i < k; ++i)
                if (it.current)
                    it.current = it.current->next;
            return it;
        }

        const_iterator operator-(int k) const
        {
            auto it{*this};
            for (int i{0}; i < k; ++i)
                if (it.current)
                    it.current = it.current->prev;
            return it;
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
        Node *current;
        bool invalidated;
        const List *theList;

        const_iterator(const List &list, Node *p)
            : current{p},
              theList{&list}
        {
        }

        T &retrieve() const
        {
            return current->data;
        }

        friend class List;
    };

    class iterator : public const_iterator
    {
    public:
        const T &operator*() const
        {
            return const_iterator::operator*();
        }

        T &operator*()
        {
            return const_iterator::retrieve();
        }

        iterator &operator++()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++(int)
        {
            auto old{*this};
            ++(*this);
            return old;
        }
        iterator &operator--()
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator--(int)
        {
            auto old{*this};
            --(*this);
            return old;
        }

        iterator operator+(int k) const
        {
            auto it{*this};
            for (int i{0}; i < k; ++i)
                if (it.current)
                    it.current = it.current->next;
            return it;
        }

        iterator operator-(int k) const
        {
            auto it{*this};
            for (int i{0}; i < k; ++i)
                if (it.current)
                    it.current = it.current->prev;
            return it;
        }

    private:
        iterator(const List &list, Node *p)
            : const_iterator{list, p} {}
        friend class List;
    };

public:
    List()
    {
        init();
    }
    // big five
    ~List()
    {
        clear();
        delete head;
        delete tail;
    }
    List(const List &rhs)
    {
        init();
        for (auto &x : rhs)
            push_back(x);
    }
    List(List &&rhs)
        : theSize{rhs.theSize},
          head{rhs.head},
          tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    void swap(List &lhs, List &rhs)
    {
        std::swap(lhs.theSize, rhs.theSize);
        std::swap(lhs.head, rhs.head);
        std::swap(lhs.tail, rhs.tail);
    }
    List &operator=(const List &rhs)
    {
        auto copy{rhs};
        swap(*this, copy);
        return *this;
    }
    List &operator=(List &&rhs)
    {
        swap(*this, rhs);
        return *this;
    }

    // iterator
    iterator begin()
    {
        return {*this, head->next};
    }
    const_iterator begin() const
    {
        return {*this, head->next};
    }
    iterator end()
    {
        return {*this, tail};
    }
    const_iterator end() const
    {
        return {*this, tail};
    }

    // container common
    int size() const
    {
        return theSize;
    }
    bool empty() const
    {
        return size() == 0;
    }
    void clear()
    {
        while (!empty())
            pop_front();
    }

    // methods
    T &front()
    {
        return *begin();
    }
    const T &front() const
    {
        return *begin();
    }
    T &back()
    {
        return *--end();
    }
    const T &back() const
    {
        return *--end();
    }
    void push_front(const T &x)
    {
        insert(begin(), x);
    }
    void push_front(T &&x)
    {
        insert(begin(), std::move(x));
    }
    void push_back(const T &x)
    {
        insert(end(), x);
    }
    void push_back(T &&x)
    {
        insert(end(), std::move(x));
    }
    void pop_front()
    {
        erase(begin());
    }
    void pop_back()
    {
        erase(--end());
    }
    iterator insert(iterator it, const T &x)
    {
        if (it.theList != this)
            return it;
        Node *p = it.current;
        ++theSize;
        return {*this, p->prev = p->prev->next = new Node{x, p->prev, p}};
    }
    iterator insert(iterator it, T &&x)
    {
        if (it.theList != this)
            return it;
        Node *p = it.current;
        ++theSize;
        return {*this, p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }
    iterator erase(iterator it)
    {
        if (it.theList != this)
            return it;
        Node *p{it.current};
        iterator retVal{*this, p->next};
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize;
        return retVal;
    }
    iterator erase(iterator from, iterator to)
    {
        for (iterator it{from}; it != to;)
            it = erase(it);
        return to;
    }

private:
    int theSize;
    Node *head;
    Node *tail;

    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &l)
{
    const char *sp[] = {"", ", "};
    int i{0};
    os << "{ ";
    for (auto &el : l)
    {
        os << sp[i] << el;
        i = 1;
    }
    return os << " }";
}

void exec()
{
    List<int> l;
    List<int> l2;
    for (int i{0}; i < 10; ++i)
        l.push_back(i);
    println(l);
    auto it{l.begin()};
    println(*it);
    println(*(it + 3));
    println(*(it - 1));
    // l.insert(it, 99);
    // println(l);
    // println(it == l.begin());
    // println(*it);
    // println("########## test stl");
    // std::list<int> list = {1, 2, 3};
    // std::list<int> list2 = {21, 22, 23};
    // println(list);
    // println(list2);
    // auto it2{list2.begin()};
    // auto it3 = list.insert(it2, 99);
    // println(list);
    // println(list2);
    // println(*it2);
    // println(*it3);
}

int main()
{
    exec();
    return 0;
}
