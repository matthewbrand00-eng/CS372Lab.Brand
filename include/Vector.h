#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <algorithm>

template <typename T>
class Vector
{
protected:
    T* data;
    std::size_t currentSize;
    std::size_t currentCapacity;

public:
    Vector();
    virtual ~Vector();

    void push_back(const T& value);

    std::size_t size() const;
    std::size_t capacity() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

protected:
    virtual void increaseCapacity();
};
template <typename T>
Vector<T>::Vector()
    : data(new T[1]), currentSize(0), currentCapacity(1)
{
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (currentSize == currentCapacity)
    {
        increaseCapacity();
    }

    data[currentSize] = value;
    ++currentSize;
}

template <typename T>
std::size_t Vector<T>::size() const
{
    return currentSize;
}

template <typename T>
std::size_t Vector<T>::capacity() const
{
    return currentCapacity;
}

template <typename T>
T& Vector<T>::operator[](std::size_t index)
{
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const
{
    return data[index];
}

template <typename T>
void Vector<T>::increaseCapacity()
{
    std::size_t newCapacity = currentCapacity * 2;

    T* newData = new T[newCapacity];

    for (std::size_t i = 0; i < currentSize; ++i)
    {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData;
    currentCapacity = newCapacity;
}

template <typename T>
class CopyVector : public Vector<T>
{
protected:
    void increaseCapacity() override
    {
        std::size_t newCapacity = this->currentCapacity * 2;

        T* newData = new T[newCapacity];

        std::copy(
            this->data,
            this->data + this->currentSize,
            newData
        );

        delete[] this->data;

        this->data = newData;
        this->currentCapacity = newCapacity;
    }
};

template <typename T>
class LargeGrowthVector : public Vector<T>
{
public:
    LargeGrowthVector()
    {
        delete[] this->data;

        this->currentCapacity = 128;
        this->currentSize = 0;
        this->data = new T[this->currentCapacity];
    }

protected:
    void increaseCapacity() override
    {
        std::size_t newCapacity = this->currentCapacity * 4;

        T* newData = new T[newCapacity];

        std::copy(
            this->data,
            this->data + this->currentSize,
            newData
        );

        delete[] this->data;

        this->data = newData;
        this->currentCapacity = newCapacity;
    }
};

#endif
