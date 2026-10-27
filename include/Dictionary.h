
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "AVLTree.h"
#include "List.h"
#include "Pair.h"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename Key, typename Value>
class Dictionary
{
private:
    using Entry = Pair<Key, Value>;

    // Compare keys only, not values.
    struct KeyCompare
    {
        bool operator()(const Entry& a, const Entry& b) const
        {
            return a.first < b.first;
        }
    };

    AVLTree<Entry, KeyCompare> tree_;
    std::size_t count_ = 0;

    // The assignment requires references to Lists.
    // These lists are cached inside the Dictionary.
    mutable List<Key> keysCache_;
    mutable List<Value> valuesCache_;

    void rebuildCaches() const
    {
        keysCache_ = List<Key>();
        valuesCache_ = List<Value>();

        tree_.inorder_traverse([&](const Entry& item)
        {
            keysCache_.push_back(item.first);
            valuesCache_.push_back(item.second);
        });
    }

public:
    // Rule of Five
    Dictionary() = default;
    Dictionary(const Dictionary&) = default;
    Dictionary& operator=(const Dictionary&) = default;
    Dictionary(Dictionary&& other) noexcept
    : tree_(std::move(other.tree_)),
      count_(std::exchange(other.count_, 0))
{
}

Dictionary& operator=(Dictionary&& other) noexcept
{
    if (this != &other)
    {
        tree_ = std::move(other.tree_);
        count_ = std::exchange(other.count_, 0);

        keysCache_ = List<Key>();
        valuesCache_ = List<Value>();
        other.keysCache_ = List<Key>();
        other.valuesCache_ = List<Value>();
    }

    return *this;
}
    ~Dictionary() = default;

    Value& operator[](const Key& key)
    {
        Entry search{key, Value{}};

        Entry* found = tree_.find(search);
        if (found)
            return found->second;

        tree_.insert(search);
        ++count_;

        return tree_.find(search)->second;
    }

    Value& at(const Key& key)
    {
        Entry search{key, Value{}};
        Entry* found = tree_.find(search);

        if (!found)
            throw std::out_of_range("Dictionary key not found");

        return found->second;
    }

    const Value& at(const Key& key) const
    {
        Entry search{key, Value{}};
        const Entry* found = tree_.find(search);

        if (!found)
            throw std::out_of_range("Dictionary key not found");

        return found->second;
    }

    void insert(const Entry& item)
    {
        if (tree_.find(item))
            return;

        tree_.insert(item);
        ++count_;
    }

    void erase(const Key& key)
    {
        Entry search{key, Value{}};

        if (!tree_.find(search))
            return;

        tree_.remove(search);
        --count_;
    }

    void clear()
    {
        tree_ = AVLTree<Entry, KeyCompare>();
        count_ = 0;
        rebuildCaches();
    }

    List<Key>& keys()
    {
        rebuildCaches();
        return keysCache_;
    }

    List<Value>& values()
    {
        rebuildCaches();
        return valuesCache_;
    }

    bool isEmpty() const
    {
        return count_ == 0;
    }

    std::size_t size() const
    {
        return count_;
    }
};

#endif
