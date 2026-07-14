#pragma once
#include <vector>
#include <algorithm>

template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right, bool (*comp)(const T&, const T&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<T> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
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
void mergeSort(std::vector<T>& arr, bool (*comp)(const T&, const T&)) {
    int n = arr.size();
    int len = 1;
    while (len < n) {
        int left = 0;
        while (left < n - len) {
            int mid = left + len - 1;
            int right = std::min(left + 2 * len - 1, n - 1);
            merge(arr, left, mid, right, comp);
            left += 2 * len;
        }
        len *= 2;
    }
}
