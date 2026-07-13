#include <vector>

template <typename T, typename Compare>
void heapify(std::vector<T>& arr, int n, int i, Compare comp) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && comp(arr[left], arr[largest]))
        largest = left;
    if (right < n && comp(arr[right], arr[largest]))
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, comp);
    }
}

template <typename T, typename Compare>
void buildHeap(std::vector<T>& arr, Compare comp) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comp);
}

template <typename T, typename Compare>
void heapSort(std::vector<T>& arr, Compare comp) {
    int n = arr.size();
    buildHeap(arr, comp);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, comp);
    }
}
