#include <iostream>

#include "matrix.h"
using namespace std;

int main()
{
    matrix<int> m;
    cout << m;
    m.resize(3, 4);
    cout << m;

    for (int r{0}; r < m.numrows(); ++r)
        for (int c{0}; c < m.numcols(); ++c)
            m[r][c] = r * m.numcols() + c;

    cout << m;

    m.resize(6, 8);

    cout << m;

    m.resize(2, 3);

    cout << m;

    return 0;
}
