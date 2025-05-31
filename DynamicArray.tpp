#pragma once

template <typename T>
DynamicArray<T>::DynamicArray()
    : m_data(nullptr), m_size(0), m_capacity(10) {
    allocate(m_capacity);
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t initialCapacity)
    : m_data(nullptr), m_size(0), m_capacity(initialCapacity) {
    allocate(m_capacity);
}

template <typename T>
DynamicArray<T>::DynamicArray(size_t count, const T& value)
    : m_data(nullptr), m_size(count), m_capacity(count) {
    allocate(m_capacity);
    for (size_t i = 0; i < count; ++i)
        m_data[i] = value;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
    : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
    allocate(m_capacity);
    for (size_t i = 0; i < m_size; ++i)
        m_data[i] = other.m_data[i];
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        destroy();
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        allocate(m_capacity);
        for (size_t i = 0; i < m_size; ++i)
            m_data[i] = other.m_data[i];
    }
    return *this;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    destroy();
}

template <typename T>
void DynamicArray<T>::allocate(size_t newCapacity) {
    m_data = new T[newCapacity];
}

template <typename T>
void DynamicArray<T>::destroy() {
    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
T& DynamicArray<T>::operator[](size_t index) {
    return m_data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](size_t index) const {
    return m_data[index];
}

template <typename T>
size_t DynamicArray<T>::size() const {
    return m_size;
}

template <typename T>
size_t DynamicArray<T>::capacity() const {
    return m_capacity;
}

template <typename T>
void DynamicArray<T>::grow() {
    size_t newCapacity = m_capacity * 2;
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < m_size; ++i)
        newData[i] = m_data[i];
    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (m_size >= m_capacity)
        grow();
    m_data[m_size++] = value;
}

template <typename T>
void DynamicArray<T>::clear() {
    m_size = 0;
}

template <typename T>
T& DynamicArray<T>::at(size_t index) {
    if (index >= m_size)
        throw std::out_of_range("Index out of range");
    return m_data[index];
}

template <typename T>
const T& DynamicArray<T>::at(size_t index) const {
    if (index >= m_size)
        throw std::out_of_range("Index out of range");
    return m_data[index];
}

template <typename T>
T& DynamicArray<T>::front() {
    if (m_size == 0)
        throw std::underflow_error("Array is empty");
    return m_data[0];
}

template <typename T>
const T& DynamicArray<T>::front() const {
    if (m_size == 0)
        throw std::underflow_error("Array is empty");
    return m_data[0];
}

template <typename T>
T& DynamicArray<T>::back() {
    if (m_size == 0)
        throw std::underflow_error("Array is empty");
    return m_data[m_size - 1];
}

template <typename T>
const T& DynamicArray<T>::back() const {
    if (m_size == 0)
        throw std::underflow_error("Array is empty");
    return m_data[m_size - 1];
}

template <typename T>
void DynamicArray<T>::pop_back() {
    if (m_size == 0)
        throw std::underflow_error("Array is empty");
    --m_size;
}

template <typename T>
void DynamicArray<T>::resize(size_t newSize) {
    if (newSize > m_capacity) {
        reserve(newSize);
    }
    if (newSize > m_size) {
        for (size_t i = m_size; i < newSize; ++i)
            m_data[i] = T();
    }
    m_size = newSize;
}

template <typename T>
void DynamicArray<T>::resize(size_t newSize, const T& value) {
    if (newSize > m_capacity) {
        reserve(newSize);
    }
    if (newSize > m_size) {
        for (size_t i = m_size; i < newSize; ++i)
            m_data[i] = value;
    }
    m_size = newSize;
}

template <typename T>
void DynamicArray<T>::reserve(size_t newCapacity) {
    if (newCapacity <= m_capacity)
        return;

    T* newData = new T[newCapacity];
    for (size_t i = 0; i < m_size; ++i)
        newData[i] = m_data[i];

    delete[] m_data;
    m_data = newData;
    m_capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::shrink_to_fit() {
    if (m_capacity == m_size)
        return;

    T* newData = new T[m_size];
    for (size_t i = 0; i < m_size; ++i)
        newData[i] = m_data[i];

    delete[] m_data;
    m_data = newData;
    m_capacity = m_size;
}

template <typename T>
template <typename... Args>
void DynamicArray<T>::emplace_back(Args&&... args) {
    if (m_size >= m_capacity)
        grow();
    m_data[m_size++] = T(std::forward<Args>(args)...);
}

template <typename T>
T* DynamicArray<T>::begin() {
    return m_data;
}

template <typename T>
const T* DynamicArray<T>::begin() const {
    return m_data;
}

template <typename T>
const T* DynamicArray<T>::cbegin() const {
    return m_data;
}

template <typename T>
T* DynamicArray<T>::end() {
    return m_data + m_size;
}

template <typename T>
const T* DynamicArray<T>::end() const {
    return m_data + m_size;
}

template <typename T>
const T* DynamicArray<T>::cend() const {
    return m_data + m_size;
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::insert(const_iterator pos, const T& value) {
    size_t index = static_cast<size_t>(pos - m_data);
    if (index > m_size)
        throw std::out_of_range("Insert position out of range");

    if (m_size >= m_capacity)
        grow();

    for (size_t i = m_size; i > index; --i)
        m_data[i] = m_data[i - 1];

    m_data[index] = value;
    ++m_size;

    return m_data + index;
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::erase(const_iterator pos) {
    size_t index = static_cast<size_t>(pos - m_data);
    if (index >= m_size)
        throw std::out_of_range("Erase position out of range");

    for (size_t i = index; i + 1 < m_size; ++i)
        m_data[i] = m_data[i + 1];

    --m_size;
    return m_data + index;
}

template <typename T>
typename DynamicArray<T>::iterator DynamicArray<T>::erase(const_iterator first, const_iterator last) {
    size_t start = static_cast<size_t>(first - m_data);
    size_t end = static_cast<size_t>(last - m_data);

    if (start > end || end > m_size)
        throw std::out_of_range("Erase range out of bounds");

    size_t count = end - start;

    for (size_t i = start; i + count < m_size; ++i)
        m_data[i] = m_data[i + count];

    m_size -= count;
    return m_data + start;
}

template <typename T>
void DynamicArray<T>::assign(size_t count, const T& value) {
    if (count > m_capacity)
        reserve(count);

    for (size_t i = 0; i < count; ++i)
        m_data[i] = value;

    m_size = count;
}

template <typename T>
template <typename InputIt>
void DynamicArray<T>::assign(InputIt first, InputIt last) {
    size_t count = static_cast<size_t>(std::distance(first, last));
    if (count > m_capacity)
        reserve(count);

    size_t i = 0;
    for (InputIt it = first; it != last; ++it, ++i)
        m_data[i] = *it;

    m_size = count;
}

template <typename T>
void DynamicArray<T>::assign(std::initializer_list<T> ilist) {
    assign(ilist.begin(), ilist.end());
}
