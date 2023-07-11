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
        bool deleted;

        Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
            : data{d}, prev{p}, next{n}, deleted{false} {}
        Node(T &&d, Node *p = nullptr, Node *n = nullptr)
            : data{std::move(d)}, prev{p}, next{n}, deleted{false} {}
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
            assertUnStale();
            return retrieve();
        }

        const_iterator &operator++()
        {
            if (*this == theList->end())
                throw std::runtime_error("iterator out of end");
            while (current->next->deleted)
                current = current->next;
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
            if (*this == theList->end())
                throw std::runtime_error("iterator out of begin");
            while (current->prev->deleted)
                current = current->prev;
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
                ++it;
            return it;
        }

        const_iterator operator-(int k) const
        {
            auto it{*this};
            for (int i{0}; i < k; ++i)
                --it;
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
        const List *theList;

        const_iterator(const List &list, Node *p)
            : current{p},
              theList{&list}
        {
        }

        void assertUnStale() const
        {
            if (current == nullptr || current->next == nullptr ||
                current->prev == nullptr || current != current->next->prev ||
                current != current->prev->next)
                throw std::runtime_error("stale iterator");
            else if (current->deleted)
                throw std::runtime_error("deleted iterator");
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
            const_iterator::assertUnStale();
            return const_iterator::operator*();
        }

        T &operator*()
        {
            const_iterator::assertUnStale();
            return const_iterator::retrieve();
        }

        iterator &operator++()
        {
            if (*this == this->theList->end())
                throw std::runtime_error("iterator out of end");
            while (this->current->next->deleted)
                this->current = this->current->next;
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
            if (*this == this->theList->end())
                throw std::runtime_error("iterator out of end");
            while (this->current->prev->deleted)
                this->current = this->current->prev;
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
                ++it;
            return it;
        }

        iterator operator-(int k) const
        {
            auto it{*this};
            for (int i{0}; i < k; ++i)
                --it;
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
        iterator begin{*this, head};
        return ++begin;
    }
    const_iterator begin() const
    {
        iterator begin{*this, head};
        return ++begin;
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
    int real_size() const
    {
        return theSize + deletedCount;
    }
    bool empty() const
    {
        return size() == 0;
    }
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
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
        p->deleted = true;
        --theSize;
        ++deletedCount;
        auto retVal{++it};
        if (deletedCount >= theSize)
            real_erase();
        return retVal;
    }
    iterator erase(iterator from, iterator to)
    {
        for (iterator it{from}; it != to;)
            it = erase(it);
        return to;
    }

    void splice(iterator pos, List<T> &list)
    {
        if (this == &list)
            return;
        Node *p{pos.current};
        Node *start{list.begin().current};
        Node *end{(--list.end()).current};
        start->prev->next = end->next;
        end->next->prev = start->prev;

        p->prev->next = start;
        start->prev = p->prev;
        end->next = p;
        p->prev = end;

        theSize += list.theSize;
        list.theSize = 0;
    }

private:
    int theSize;
    int deletedCount;
    Node *head;
    Node *tail;

    void init()
    {
        theSize = 0;
        deletedCount = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
    void real_erase()
    {
        Node *p{head->next};
        while (p != tail)
        {
            Node *temp{p->next};
            if (p->deleted)
            {
                p->prev->next = p->next;
                p->next->prev = p->prev;
                delete p;
            }
            p = temp;
        }
        deletedCount = 0;
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
    for (int i{0}; i < 5; ++i)
        l2.push_back(i);

    println(l);
    auto it{l.begin()};
    it = l.erase(it + 1);
    println(l);
    it = l.insert(it, 99);
    // it = l.erase(it + 1);
    // it = l.erase(it + 1);
    // it = l.erase(it + 1);
    println(l);
    println(l.size());
    println(l.real_size());
    println(*it);

    // println(l2);
    // l.splice(l.begin() + 2, l2);
    // println(l);
    // println(l2);
    // println("#############");

    // auto it{l.begin()};
    // println(*it);
    // println(*(it + 3));
    // println(*(it - 1));
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
