#pragma once
#include <vector>

template <typename T>
int partition(std::vector<T>& arr, int low, int high, bool (*comp)(const T&, const T&)) {
    T pivot = arr[high];
    int i = low - 1;
    // comp(a, b) = a < b  -> orden ascendente
    // comp(a, b) = a > b  -> orden descendente
    for (int j = low; j < high; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSort(std::vector<T>& arr, int low, int high, bool (*comp)(const T&, const T&)) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSort(arr, low, pi - 1, comp);
        quickSort(arr, pi + 1, high, comp);
    }
}

template <typename T>
void quickSort(std::vector<T>& arr, bool (*comp)(const T&, const T&)) {
    quickSort(arr, 0, arr.size() - 1, comp);
}
