#include <iostream>
#include "DynamicArray.hpp"

int main() {
    DynamicArray<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    for (size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    arr.resize(10, -1);
    std::cout << "After resize:\n";
    for (size_t i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";

    arr.emplace_back(99);

    std::cout << "Range loop:\n";
    for (int v : arr)
        std::cout << v << " ";
    std::cout << "\n";

    arr.insert(arr.begin() + 1, 99);

    arr.erase(arr.begin() + 2);

    arr.erase(arr.begin() + 3, arr.begin() + 6);

    arr.assign(5, 42);

    DynamicArray<int> other;
    other.assign({ 1, 2, 3, 4, 5 });

}
