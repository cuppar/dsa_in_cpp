#include <iostream>
#include <vector>
#include "util.h"

template <typename T>
class Tree
{
private:
    struct Node
    {
        T element;
        Node *left;
        Node *right;

        Node(const T element, Node *left, Node *right)
            : element{element},
              left{left},
              right{right}
        {
        }
    };
    Node *root;

public:
    Tree(std::string_view s)
    {
        std::vector<Node *> stack;
        for (auto ch : s)
        {
            if (std::isalnum(ch))
            {
                Node *n = new Node{ch, nullptr, nullptr};
                stack.push_back(n);
            }
            else
            {
                Node *right = stack.back();
                stack.pop_back();
                Node *left = stack.back();
                stack.pop_back();
                Node *n = new Node{ch, left, right};
                stack.push_back(n);
            }
        }
        root = stack.back();
    }

    void print() const
    {
        print(root, 0);
    }

    void print(const Node *n, int depth) const
    {
        if (n)
        {
            print(n->right, depth + 1);
            for (int i{0}; i < depth; ++i)
                std::cout << "    ";
            std::cout << n->element << '\n';
            print(n->left, depth + 1);
        }
    }
};

void exec()
{
    Tree<char> t{"ab+cde+**"};
    t.print();
}

int main()
{
    exec();
    return 0;
}
