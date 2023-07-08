#include <iostream>
#include "util.h"

bool martix_has2(matrix<int> m, int x)
{
    int i{0};
    int j{m.numrows() - 1};

    while (i < m.numrows() && j >= 0)
    {
        if (m[i][j] == x)
            return true;

        else if (m[i][j] < x)
            ++i;

        else
            --j;
    }

    return false;
}
bool martix_has(matrix<int> m, int x)
{
    int rows{m.numrows()};
    int cols{m.numrows()};
    int left_col{0};
    int right_col{cols - 1};

    while (left_col < right_col)
    {
        int mid{(left_col + right_col + 1) / 2};

        if (m[0][mid] < x)
            left_col = mid;

        else if (m[0][mid] > x)
            right_col = mid - 1;

        else
            return true;
    }

    if (left_col > right_col)
        return false;

    // now only one col
    int top_row{0};
    int btm_row{rows - 1};

    while (top_row <= btm_row)
    {
        int mid{(top_row + btm_row) / 2};

        if (m[mid][left_col] > x)
            btm_row = mid - 1;

        else if (m[mid][left_col] < x)
            top_row = mid + 1;

        else
            return true;
    }

    return false;
}

void exec()
{
    matrix<int> m
    {
        {
            {1, 5, 9},
            {2, 12, 23},
            {3, 18, 34},

        }
    };
    println(martix_has2(m, 34));
}

int main()
{
    exec();
    return 0;
}
