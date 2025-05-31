#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <initializer_list>
#include <iterator>


template <typename T>
class DynamicArray {
public:

    DynamicArray();
    DynamicArray(size_t initialCapacity);
    DynamicArray(size_t count, const T& value);
    DynamicArray(const DynamicArray& other);

    DynamicArray& operator=(const DynamicArray& other);

    ~DynamicArray();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t size() const;
    size_t capacity() const;

    void push_back(const T& value);
    void clear();

    T& at(size_t index);
    const T& at(size_t index) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    void pop_back();

    void resize(size_t newSize);
    void resize(size_t newSize, const T& value);
    void reserve(size_t newCapacity);
    void shrink_to_fit();

    template <typename... Args>
    void emplace_back(Args&&... args);

    T* begin();
    const T* begin() const;
    const T* cbegin() const;

    T* end();
    const T* end() const;
    const T* cend() const;

    using iterator = T*;
    using const_iterator = const T*;

    iterator insert(const_iterator pos, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void assign(size_t count, const T& value);

    template <typename InputIt>
    void assign(InputIt first, InputIt last);

    void assign(std::initializer_list<T> ilist);



private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void grow();
    void allocate(size_t newCapacity);
    void destroy();
};

#include "DynamicArray.tpp"

#endif
