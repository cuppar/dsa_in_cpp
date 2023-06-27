#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "matrix.h"

struct Point
{
    int x;
    int y;
};
bool operator==(const Point& a, const Point& b)
{
    return a.x == b.x && a.y == b.y;
}

struct Word
{
    Point start;
    Point end;
};
std::ostream& operator<<(std::ostream& out, const Word& word)
{
    out << "Word(Start[" << word.start.x << "][" << word.start.y <<
        "], End[" << word.end.x << "][" << word.end.y << "])";
    return out;
}

using WordPuzzle = matrix<char>;
using Dictionary = std::vector<std::string>;

// input a puzz and dict, return a word list
std::vector<Word> wordPuzzle(WordPuzzle puzz, Dictionary dict)
{
    std::vector<Word> result;

    for (auto& word : dict)
    {
        for (int row{0}; row < puzz.numrows(); ++row)
        {
            for (int col{0}; col < puzz.numcols(); ++col)
            {
                int r{row};
                int c{col};
                int cur{0};

                // right
                while (c < puzz.numcols()
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    ++c;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(r, --c)
                    --c;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // right-down
                while (c < puzz.numcols()
                        && r < puzz.numrows()
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    ++c;
                    ++r;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(--r, --c)
                    --c;
                    --r;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // down
                while (
                    r < puzz.numrows()
                    && cur < static_cast<int>(word.size())
                    && word[cur] == puzz[r][c])
                {
                    ++r;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(--r, c)
                    --r;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // left-down
                while (c >= 0
                        && r < puzz.numrows()
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    --c;
                    ++r;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(--r, ++c)
                    ++c;
                    --r;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // left
                while (c >= 0
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    --c;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(r, ++c)
                    ++c;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // left-up
                while (c >= 0
                        && r >= 0
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    --c;
                    --r;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(++r, ++c)
                    ++c;
                    ++r;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // up
                while (r >= 0
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    --r;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(++r, c)
                    ++r;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }

                r = row;
                c = col;
                cur = 0;

                // up-right
                while (r >= 0
                        && c < puzz.numcols()
                        && cur < static_cast<int>(word.size())
                        && word[cur] == puzz[r][c])
                {
                    --r;
                    ++c;
                    ++cur;
                }

                if (cur >= static_cast<int>(word.size()))
                {
                    // match start(row, col), end(++r, --c)
                    ++r;
                    --c;
                    result.push_back(Word{Point{row + 1, col + 1}, Point{r + 1, c + 1}});
                }
            }
        }
    }

    return result;
}

bool test()
{
    WordPuzzle puzz{std::vector<std::vector<char>>{
            {'t', 'h', 'i', 's'},
            {'w', 'a', 't', 's'},
            {'o', 'a', 'h', 'g'},
            {'f', 'g', 'd', 't'},
        }};
    Dictionary dict{"this", "two", "fat", "that"};
    auto wordList {wordPuzzle(puzz, dict)};
    std::cout << "Word Puzzle:\n";
    std::cout << puzz << '\n';
    std::cout << "Dictionary:\n";

    for (const auto& word : dict)
        std::cout << word << ' ';

    std::cout << "\n\nResult:\n";

    for (const auto& word : wordList)
        std::cout << word << '\n';

    if (wordList.size() != 4)
        return false;

    return wordList[0].start == Point{1, 1}
           && wordList[0].end == Point{1, 4}
           && wordList[1].start == Point{1, 1}
           && wordList[1].end == Point{3, 1}
           && wordList[2].start == Point{4, 1}
           && wordList[2].end == Point{2, 3}
           && wordList[3].start == Point{4, 4}
           && wordList[3].end == Point{1, 1};
}
int main()
{
    auto ispass{test()};
    std::cout << "\n##### test " << (ispass ? "pass" : "fial") << '\n';
    return 0;
}
