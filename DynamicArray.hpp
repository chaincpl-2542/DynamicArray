#pragma once
#include <stdexcept>
#include <cstddef>

template<typename T>
class DynamicArray {
private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < m_size; ++i) {
            newData[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }

public:
    DynamicArray() : m_data(new T[10]), m_size(0), m_capacity(10) {}

    DynamicArray(size_t initialCapacity) : m_data(new T[initialCapacity]), m_size(0), m_capacity(initialCapacity) {}

    DynamicArray(size_t count, const T& value) : m_data(new T[count]), m_size(count), m_capacity(count) {
        for (size_t i = 0; i < count; ++i) m_data[i] = value;
    }

    DynamicArray(const DynamicArray& other) : m_data(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
        for (size_t i = 0; i < other.m_size; ++i) m_data[i] = other.m_data[i];
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = new T[other.m_capacity];
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            for (size_t i = 0; i < other.m_size; ++i) m_data[i] = other.m_data[i];
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] m_data;
    }

    T& at(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }

    const T& at(size_t index) const {
        if (index >= m_size) throw std::out_of_range("Index out of bounds");
        return m_data[index];
    }

    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }

    T& front() {
        if (m_size == 0) throw std::underflow_error("Array is empty");
        return m_data[0];
    }

    const T& front() const {
        if (m_size == 0) throw std::underflow_error("Array is empty");
        return m_data[0];
    }

    T& back() {
        if (m_size == 0) throw std::underflow_error("Array is empty");
        return m_data[m_size - 1];
    }

    const T& back() const {
        if (m_size == 0) throw std::underflow_error("Array is empty");
        return m_data[m_size - 1];
    }

    T* data_ptr() { return m_data; }
    const T* data_ptr() const { return m_data; }

    void push_back(const T& value) {
        if (m_size >= m_capacity) reallocate(m_capacity * 2);
        m_data[m_size++] = value;
    }

    void pop_back() {
        if (m_size == 0) throw std::underflow_error("Array is empty");
        --m_size;
    }

    void clear() {
        m_size = 0;
    }

    void resize(size_t newSize) {
        if (newSize > m_capacity) reallocate(newSize);
        m_size = newSize;
    }

    void resize(size_t newSize, const T& value) {
        if (newSize > m_capacity) reallocate(newSize);
        for (size_t i = m_size; i < newSize; ++i) m_data[i] = value;
        m_size = newSize;
    }

    void reserve(size_t newCapacity) {
        if (newCapacity > m_capacity) reallocate(newCapacity);
    }

    void shrink_to_fit() {
        if (m_size < m_capacity) reallocate(m_size);
    }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }
    size_t memory_usage() const { return m_capacity * sizeof(T); }
};