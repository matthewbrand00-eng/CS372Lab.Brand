
#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <memory>
#include <utility>

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        std::weak_ptr<Node> prev;
        std::shared_ptr<Node> next;

        Node(const T& value = T{})
            : data(value), prev(), next(nullptr)
        {
        }
    };

public:
    class iterator
    {
        friend class List<T>;

    private:
        Node* current;

        explicit iterator(Node* node) : current(node) {}

    public:
        iterator() : current(nullptr) {}

        T& operator*() const
        {
            return current->data;
        }

        iterator& operator++()
        {
            current = current->next.get();
            return *this;
        }

        iterator operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator--()
        {
            current = current->prev.lock().get();
            return *this;
        }

        bool operator==(const iterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const
        {
            return current != other.current;
        }
    };

    class const_iterator
    {
        friend class List<T>;

    private:
        const Node* current;

        explicit const_iterator(const Node* node) : current(node) {}

    public:
        const_iterator() : current(nullptr) {}

        const T& operator*() const
        {
            return current->data;
        }

        const_iterator& operator++()
        {
            current = current->next.get();
            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator--()
        {
            current = current->prev.lock().get();
            return *this;
        }

        bool operator==(const const_iterator& other) const
        {
            return current == other.current;
        }

        bool operator!=(const const_iterator& other) const
        {
            return current != other.current;
        }
    };

protected:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    std::size_t listSize;

    void initialize()
    {
        head = std::make_shared<Node>();
        tail = std::make_shared<Node>();

        head->next = tail;
        tail->prev = head;

        listSize = 0;
    }

    void clear()
    {
        if (!head || !tail)
            return;

        head->next = tail;
        tail->prev = head;
        listSize = 0;
    }

public:
    List()
    {
        initialize();
    }

    List(const List& other) : List()
    {
        for (const auto& item : other)
        {
            push_back(item);
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            List temp(other);
            swap(temp);
        }
        return *this;
    }

    List(List&& other) : List()
    {
        swap(other);
    }

    List& operator=(List&& other)
    {
        if (this != &other)
        {
            swap(other);
            other.clear();
        }
        return *this;
    }

    virtual ~List() = default;

    void swap(List& other) noexcept
    {
        using std::swap;
        swap(head, other.head);
        swap(tail, other.tail);
        swap(listSize, other.listSize);
    }

    bool empty() const
    {
        return listSize == 0;
    }

    std::size_t size() const
    {
        return listSize;
    }

    T& front()
    {
        return head->next->data;
    }

    const T& front() const
    {
        return head->next->data;
    }

    T& back()
    {
        return tail->prev.lock()->data;
    }

    const T& back() const
    {
        return tail->prev.lock()->data;
    }

    void push_front(const T& value)
    {
        insert(begin(), value);
    }

    void push_back(const T& value)
    {
        insert(end(), value);
    }

    void pop_front()
    {
        if (!empty())
        {
            erase(begin());
        }
    }

    void pop_back()
    {
        if (!empty())
        {
            erase(iterator(tail->prev.lock().get()));
        }
    }

    T& operator[](std::size_t index)
    {
        Node* current = head->next.get();

        for (std::size_t i = 0; i < index; ++i)
        {
            current = current->next.get();
        }

        return current->data;
    }

    const T& operator[](std::size_t index) const
    {
        const Node* current = head->next.get();

        for (std::size_t i = 0; i < index; ++i)
        {
            current = current->next.get();
        }

        return current->data;
    }

    iterator begin()
    {
        return iterator(head->next.get());
    }

    iterator end()
    {
        return iterator(tail.get());
    }

    const_iterator begin() const
    {
        return const_iterator(head->next.get());
    }

    const_iterator end() const
    {
        return const_iterator(tail.get());
    }

    const_iterator cbegin() const
    {
        return const_iterator(head->next.get());
    }

    const_iterator cend() const
    {
        return const_iterator(tail.get());
    }

    iterator insert(iterator position, const T& value)
    {
        Node* current = position.current;
        auto previous = current->prev.lock();
        auto newNode = std::make_shared<Node>(value);

        newNode->prev = previous;
        newNode->next = previous->next;

        previous->next = newNode;
        current->prev = newNode;

        ++listSize;

        return iterator(newNode.get());
    }

    iterator erase(iterator position)
    {
        Node* current = position.current;

        if (current == tail.get())
        {
            return end();
        }

        auto previous = current->prev.lock();
        auto nextNode = current->next;

        previous->next = nextNode;
        nextNode->prev = previous;

        --listSize;

        return iterator(nextNode.get());
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last)
        {
            first = erase(first);
        }

        return last;
    }
};

#endif
