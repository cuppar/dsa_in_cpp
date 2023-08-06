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

    const T &findMin() const;
    const T &findMax() const;
    bool contains(const T &x) const;
    bool isEmpty() const;
    void printTree(std::ostream &out = std::cout) const;

    void makeEmpty()
    {
        makeEmpty(root);
    }
    void insert(const T &x);
    void insert(T &&x);
    void remove(const T &x);

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
    void printTree(Node *t, std::ostream &out) const;
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
