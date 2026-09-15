#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <utility>

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value = T{}, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n)
        {
        }
    };

public:
    class iterator
    {
        friend class List<T>;

    private:
        Node* current;

        explicit iterator(Node* node)
            : current(node)
        {
        }

    public:
        iterator()
            : current(nullptr)
        {
        }

        T& operator*() const
        {
            return current->data;
        }

        iterator& operator++()
        {
            current = current->next;
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
            current = current->prev;
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

        explicit const_iterator(const Node* node)
            : current(node)
        {
        }

    public:
        const_iterator()
            : current(nullptr)
        {
        }

        const T& operator*() const
        {
            return current->data;
        }

        const_iterator& operator++()
        {
            current = current->next;
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
            current = current->prev;
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
    Node* head;
    Node* tail;
    std::size_t listSize;

    void initialize()
    {
        head = new Node;
        tail = new Node;

        head->next = tail;
        tail->prev = head;

        listSize = 0;
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

public:
    List()
    {
        initialize();
    }

    List(const List& other)
    {
        initialize();

        for (const auto& item : other)
        {
            push_back(item);
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            clear();

            for (const auto& item : other)
            {
                push_back(item);
            }
        }

        return *this;
    }

    List(List&& other) noexcept
        : head(other.head),
          tail(other.tail),
          listSize(other.listSize)
    {
        other.initialize();
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            clear();

            delete head;
            delete tail;

            head = other.head;
            tail = other.tail;
            listSize = other.listSize;

            other.initialize();
        }

        return *this;
    }

    virtual ~List()
    {
        clear();

        delete head;
        delete tail;
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
        return tail->prev->data;
    }

    const T& back() const
    {
        return tail->prev->data;
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
            iterator temp(tail->prev);
            erase(temp);
        }
    }

    T& operator[](std::size_t index)
    {
        Node* current = head->next;

        for (std::size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }

        return current->data;
    }

    const T& operator[](std::size_t index) const
    {
        const Node* current = head->next;

        for (std::size_t i = 0; i < index; ++i)
        {
            current = current->next;
        }

        return current->data;
    }

    iterator begin()
    {
        return iterator(head->next);
    }

    iterator end()
    {
        return iterator(tail);
    }

    const_iterator begin() const
    {
        return const_iterator(head->next);
    }

    const_iterator end() const
    {
        return const_iterator(tail);
    }

    const_iterator cbegin() const
    {
        return const_iterator(head->next);
    }

    const_iterator cend() const
    {
        return const_iterator(tail);
    }

    iterator insert(iterator position, const T& value)
    {
        Node* current = position.current;

        Node* newNode = new Node(
            value,
            current->prev,
            current
        );

        current->prev->next = newNode;
        current->prev = newNode;

        ++listSize;

        return iterator(newNode);
    }

    iterator erase(iterator position)
    {
        Node* current = position.current;

        if (current == tail)
        {
            return end();
        }

        Node* nextNode = current->next;

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;

        --listSize;

        return iterator(nextNode);
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
