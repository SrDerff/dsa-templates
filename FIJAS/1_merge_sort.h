#pragma once
#include <vector>

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right, bool (*comp)(const T&, const T&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<T> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    // comp(a, b) = a < b  -> orden ascendente
    // comp(a, b) = a > b  -> orden descendente
    while (i < n1 && j < n2) {
        if (comp(L[i], R[j]))
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right, bool (*comp)(const T&, const T&)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

template <typename T>
void mergeSort(std::vector<T>& arr, bool (*comp)(const T&, const T&)) {
    mergeSort(arr, 0, arr.size() - 1, comp);
}
