#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

template <typename T>
class Array
{
private:
    T* data;
    std::size_t arraySize;

public:
    explicit Array(std::size_t size);

    Array(const Array& other);

    Array& operator=(const Array& other);

    ~Array();

    std::size_t size() const;

    T& operator[](std::size_t index);

    const T& operator[](std::size_t index) const;
};

template <typename T>
Array<T>::Array(std::size_t size)
    : data(new T[size]), arraySize(size)
{
}

template <typename T>
Array<T>::Array(const Array& other)
    : data(new T[other.arraySize]),
      arraySize(other.arraySize)
{
    for (std::size_t i = 0; i < arraySize; ++i)
    {
        data[i] = other.data[i];
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    if (this != &other)
    {
        T* newData = new T[other.arraySize];

        for (std::size_t i = 0; i < other.arraySize; ++i)
        {
            newData[i] = other.data[i];
        }

        delete[] data;

        data = newData;
        arraySize = other.arraySize;
    }

    return *this;
}

template <typename T>
Array<T>::~Array()
{
    delete[] data;
}

template <typename T>
std::size_t Array<T>::size() const
{
    return arraySize;
}

template <typename T>
T& Array<T>::operator[](std::size_t index)
{
    return data[index];
}

template <typename T>
const T& Array<T>::operator[](std::size_t index) const
{
    return data[index];
}

#endif

