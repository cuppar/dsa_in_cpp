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
        return root == nullptr;
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

    void insert(const T &x, Node *&t)
    {
        if (t == nullptr)
            t = new Node{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ; // do nothing.
    }
    void insert(T &&x, Node *&t)
    {
        if (t == nullptr)
            t = new Node{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
            ; // do nothing.
    }
    void remove(const T &x, Node *&t)
    {
        if (t == nullptr)
            return;
        else if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else
        {
            if (t->left == nullptr || t->right == nullptr)
            {
                Node *oldNode = t;
                t = t->left ? t->left : t->right;
                delete oldNode;
            }
            else
            {
                t->element = findmin(t->right)->element;
                remove(t->element, t->right);
            }
        }
    }
    Node *findMin(Node *t) const
    {
        if (t != nullptr)
            while (t->left != nullptr)
                t = t->left;
        return t;
    }
    Node *findMax(Node *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->right == nullptr)
            return t;
        return findMax(t->right);
    }
    bool contains(const T &x, Node *t) const
    {
        if (t == nullptr)
            return false;
        else if (t->element == x)
            return true;
        else if (x < t->element)
            return contains(x, t->left);
        else
            return contains(x, t->right);
    }
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
    BST<int> t{};
    std::vector<int> v{6, 2, 1, 4, 3, 8};
    for (auto i : v)
        t.insert(i);
    t.printTree();
}

int main()
{
    exec();
    return 0;
}
