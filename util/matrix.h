#ifndef MATRIX_H
#define MATRIX_H

#include <ostream>
#include <vector>
template <typename T>
class matrix
{
public:
    matrix() = default;
    matrix(int rows, int cols)
        : array(rows)
    {
        for (auto& thisRow : array)
            thisRow.resize(cols);
    }
    matrix(const std::vector<std::vector<T>>& v): array{v} {}
    matrix(std::vector<std::vector<T>>&& v): array{std::move(v)} {}
    void resize(int rows, int cols)
    {
        array.resize(rows);

        for (auto& thisRow : array)
            thisRow.resize(cols);
    }

    const std::vector<T>& operator[](int row) const
    {
        return array[row];
    }
    std::vector<T>& operator[](int row)
    {
        return array[row];
    }

    int numrows()const
    {
        return array.size();
    }
    int numcols()const
    {
        return numrows() ? array[0].size() : 0;
    }
    void print(std::ostream& out)
    {
        out << "matrix(" << numrows() << ", " << numcols() << ")\n";

        for (const auto& row : array)
        {
            for (const auto& col : row)
                out << col << ' ';

            out << '\n';
        }
    }

private:
    std::vector<std::vector<T>> array;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, matrix<T> m)
{
    m.print(out);
    return out;
}

#endif
