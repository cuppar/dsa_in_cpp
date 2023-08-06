#include <iostream>
#include "util.h"

template <typename T>
class BST
{
public:
    BST() : root{nullptr} {}
    BST(const BST &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }
    BST(BST &&rhs) : root{std::move(rhs.root)} {}
    ~BST()
    {
        makeEmpty();
    }
    void swap(BST &lhs, BST &rhs)
    {
        std::swap(lhs.root, rhs.root);
    }
    BST &operator=(const BST &rhs)
    {
        auto copy{rhs};
        swap(*this, copy);
        return *this;
    }
    BST &operator=(BST &&rhs)
    {
        swap(*this, rhs);
    }

    const T &findMin() const
    {
        return findMin(root);
    }
    const T &findMax() const
    {
        return findMax(root);
    }
    bool contains(const T &x) const
    {
        return contains(x, root);
    }
    bool isEmpty() const
    {
        root == nullptr
    }
    void printTree(std::ostream &out = std::cout) const
    {
        printTree(root, out);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }
    void insert(const T &x)
    {
        insert(x, root);
    }
    void insert(T &&x)
    {
        insert(std::move(x), root);
    }
    void remove(const T &x)
    {
        remove(x, root);
    }

private:
    struct Node
    {
        T element;
        Node *left;
        Node *right;

        Node(const T &el, Node *lt, Node *rt)
            : element{el}, left{lt}, right{rt}
        {
        }
        Node(T &&el, Node *lt, Node *rt)
            : element{std::move(el)}, left{lt}, right{rt}
        {
        }
    };

    Node *root;

    void insert(const T &x, Node *&t);
    void insert(T &&x, Node *&t);
    void remove(const T &x, Node *&t);
    Node *findMin(Node *t) const;
    Node *findMax(Node *t) const;
    bool contains(const T &x, Node *t) const;
    void makeEmpty(Node *&t)
    {
        if (!t)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }
    void printTree(Node *t, std::ostream &out, int depth = 0) const
    {
        if (!t)
            return;
        printTree(t->right, out, depth + 1);
        for (int i{0}; i < depth; ++i)
            out << "    ";
        out << t->element << '\n';
        printTree(t->left, out, depth + 1);
    }
    Node *clone(Node *t) const
    {
        if (!t)
            return nullptr;
        return new Node{t->element, clone(t->left), clone(t->right)};
    }
};

void exec()
{
}

int main()
{
    exec();
    return 0;
}
