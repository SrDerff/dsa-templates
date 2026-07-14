#pragma once
#include <vector>

template <typename T>
void heapify(std::vector<T>& arr, int n, int i, bool (*comp)(const T&, const T&)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // comp(a, b) = a < b  -> orden ascendente (max-heap)
    // comp(a, b) = a > b  -> orden descendente (min-heap)
    if (left < n && comp(arr[largest], arr[left]))
        largest = left;
    if (right < n && comp(arr[largest], arr[right]))
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, comp);
    }
}

template <typename T>
void heapSort(std::vector<T>& arr, bool (*comp)(const T&, const T&)) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comp);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, comp);
    }
}
