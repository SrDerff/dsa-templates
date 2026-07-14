#pragma once
#include <vector>

template <typename T>
int medianOf3(std::vector<T>& arr, int low, int high, bool (*comp)(const T&, const T&)) {
    int mid = low + (high - low) / 2;
    if (comp(arr[mid], arr[low]))
        std::swap(arr[low], arr[mid]);
    if (comp(arr[high], arr[low]))
        std::swap(arr[low], arr[high]);
    if (comp(arr[high], arr[mid]))
        std::swap(arr[mid], arr[high]);
    return mid;
}
// Mediana de 3 evita el peor caso O(n²) en arrays parcialmente ordenados
// al elegir un pivote más cercano al valor central real del subarray.

template <typename T>
int hoarePartition(std::vector<T>& arr, int low, int high, bool (*comp)(const T&, const T&)) {
    int mid = medianOf3(arr, low, high, comp);
    T pivot = arr[mid];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do { i++; } while (comp(arr[i], pivot));
        do { j--; } while (comp(pivot, arr[j]));
        if (i >= j) return j;
        std::swap(arr[i], arr[j]);
    }
}
// Hoare realiza ~3x menos intercambios que Lomuto usando dos punteros
// que se cruzan desde los extremos, particionando en O(n).

template <typename T>
void quickSort(std::vector<T>& arr, int low, int high, bool (*comp)(const T&, const T&)) {
    while (low < high) {
        int pi = hoarePartition(arr, low, high, comp);
        if (pi - low < high - pi) {
            quickSort(arr, low, pi, comp);
            low = pi + 1;
        } else {
            quickSort(arr, pi + 1, high, comp);
            high = pi;
        }
    }
}

template <typename T>
void quickSort(std::vector<T>& arr, bool (*comp)(const T&, const T&)) {
    quickSort(arr, 0, arr.size() - 1, comp);
}
