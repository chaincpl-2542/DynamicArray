#include <iostream>
#include "DynamicArray.hpp"

int main() {
    DynamicArray<int> arr;

    for (int i = 1; i <= 20; ++i) {
        arr.push_back(i);
    }

    std::cout << "Array contents: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Size: " << arr.size() << std::endl;
    std::cout << "Capacity: " << arr.capacity() << std::endl;

    arr.pop_back();
    arr.pop_back();

    std::cout << "After popping 2 elements: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Front: " << arr.front() << ", Back: " << arr.back() << std::endl;

    arr.clear();
    std::cout << "After clear, is empty: " << arr.empty() << std::endl;
    std::cout << "Capacity after clear (should not shrink): " << arr.capacity() << std::endl;

    return 0;
}
