
#ifndef TREE_H
#define TREE_H

#include <cassert>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class Tree
{
private:
    struct Node
    {
        T _val;
        std::shared_ptr<Node> _lft;
        std::shared_ptr<Node> _rgt;
        std::weak_ptr<Node> _parent;

        explicit Node(const T& value)
            : _val(value), _lft(nullptr), _rgt(nullptr) {}
    };

    std::shared_ptr<Node> _root;

    // Make independent copies so parent pointers stay correct.
    static std::shared_ptr<Node> clone(
        const std::shared_ptr<Node>& source,
        const std::shared_ptr<Node>& parent = nullptr)
    {
        if (!source)
            return nullptr;

        auto node = std::make_shared<Node>(source->_val);
        node->_parent = parent;

        node->_lft = clone(source->_lft, node);
        node->_rgt = clone(source->_rgt, node);

        return node;
    }

    explicit Tree(const std::shared_ptr<Node>& node)
        : _root(clone(node)) {}

    static std::size_t count(const std::shared_ptr<Node>& node)
    {
        if (!node)
            return 0;

        return 1 + count(node->_lft) + count(node->_rgt);
    }

public:
    Tree() : _root(nullptr) {}

    Tree(const Tree& other)
        : _root(clone(other._root)) {}

    Tree& operator=(const Tree& other)
    {
        if (this != &other)
            _root = clone(other._root);

        return *this;
    }

    Tree(Tree&& other) noexcept = default;
    Tree& operator=(Tree&& other) noexcept = default;

    ~Tree() = default;

    Tree(Tree leftTree, T value, Tree rightTree)
    {
        _root = std::make_shared<Node>(value);

        _root->_lft = clone(leftTree._root, _root);
        _root->_rgt = clone(rightTree._root, _root);
    }

    Tree(std::initializer_list<T> values) : Tree()
    {
        for (const auto& value : values)
            *this = insert(value);
    }

    bool isEmpty() const
    {
        return _root == nullptr;
    }

    std::size_t size() const
    {
        return count(_root);
    }

    const T& root() const
    {
        assert(!isEmpty());
        return _root->_val;
    }

    Tree left() const
    {
        assert(!isEmpty());
        return Tree(_root->_lft);
    }

    Tree right() const
    {
        assert(!isEmpty());
        return Tree(_root->_rgt);
    }

    // The root has no parent.
    bool hasParent() const
    {
        return _root && !_root->_parent.expired();
    }

    // Check parent relationships throughout the tree.
    bool validParents() const
    {
        auto check = [&](auto&& self,
                         const std::shared_ptr<Node>& node,
                         const std::shared_ptr<Node>& parent) -> bool
        {
            if (!node)
                return true;

            if (node->_parent.lock() != parent)
                return false;

            return self(self, node->_lft, node)
                && self(self, node->_rgt, node);
        };

        return check(check, _root, nullptr);
    }

    template <typename Compare = std::greater<T>>
    Tree insert(const T& value,
                Compare comp = Compare()) const
    {
        Tree result(*this);

        if (!result._root)
        {
            result._root = std::make_shared<Node>(value);
            return result;
        }

        auto current = result._root;

        while (true)
        {
            if (comp(value, current->_val))
            {
                if (current->_lft)
                {
                    current = current->_lft;
                }
                else
                {
                    current->_lft = std::make_shared<Node>(value);
                    current->_lft->_parent = current;
                    break;
                }
            }
            else if (comp(current->_val, value))
            {
                if (current->_rgt)
                {
                    current = current->_rgt;
                }
                else
                {
                    current->_rgt = std::make_shared<Node>(value);
                    current->_rgt->_parent = current;
                    break;
                }
            }
            else
            {
                break; // No duplicates
            }
        }

        return result;
    }

    template <typename Compare = std::greater<T>>
    bool member(const T& value,
                Compare comp = Compare()) const
    {
        auto current = _root;

        while (current)
        {
            if (comp(value, current->_val))
                current = current->_lft;
            else if (comp(current->_val, value))
                current = current->_rgt;
            else
                return true;
        }

        return false;
    }

    template <typename Compare = std::greater<T>>
    bool find(const T& value,
              Tree& subtreeWhereFound,
              Compare comp = Compare()) const
    {
        auto current = _root;

        while (current)
        {
            if (comp(value, current->_val))
                current = current->_lft;
            else if (comp(current->_val, value))
                current = current->_rgt;
            else
            {
                subtreeWhereFound = Tree(current);
                return true;
            }
        }

        subtreeWhereFound = Tree();
        return false;
    }

    template <typename Visitor>
    void preorder(Visitor visit) const
    {
        auto walk = [&](auto&& self,
                        const std::shared_ptr<Node>& node) -> void
        {
            if (!node)
                return;

            visit(node->_val);
            self(self, node->_lft);
            self(self, node->_rgt);
        };

        walk(walk, _root);
    }

    template <typename Visitor>
    void inorder(Visitor visit) const
    {
        auto walk = [&](auto&& self,
                        const std::shared_ptr<Node>& node) -> void
        {
            if (!node)
                return;

            self(self, node->_lft);
            visit(node->_val);
            self(self, node->_rgt);
        };

        walk(walk, _root);
    }

    template <typename Visitor>
    void postorder(Visitor visit) const
    {
        auto walk = [&](auto&& self,
                        const std::shared_ptr<Node>& node) -> void
        {
            if (!node)
                return;

            self(self, node->_lft);
            self(self, node->_rgt);
            visit(node->_val);
        };

        walk(walk, _root);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Tree<T>& tree)
{
    tree.inorder([&](const T& value)
    {
        out << value << ' ';
    });

    return out;
}

#endif
