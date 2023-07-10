#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include "Timer.h"
#include "Random.h"
#include "matrix.h"

template <template <class, class> class Container,
          class T, class Alloc = std::allocator <T> >
std::ostream & operator << (
    std::ostream& os,
    const Container <T, Alloc>& container)
{
    const char* sep[] = { "", ", " };
    int si = 0;
    os << "{ ";

    for (const T& elt : container)
    {
        os << sep[si] << elt;
        si = 1;
    }

    return os << " }";
}

template <typename ...Args>
void print(const Args& ...args)
{
    (std::cout << ... << args);
}

template <typename ...Args>
void println(const Args& ...args)
{
    (std::cout << ... << args) << '\n';
}
#endif
