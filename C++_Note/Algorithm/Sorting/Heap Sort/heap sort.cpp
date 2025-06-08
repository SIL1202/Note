#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

void printFancyHeap(int heap[], int n) {
  int height = log2(n) + 1;
  int maxWidth = pow(2, height - 1);

  int idx = 0;
  for (int level = 0; level < height; ++level) {
    int levelCount = pow(2, level);
    int spaceBefore = (maxWidth / levelCount) - 1;
    int spaceBetween = (maxWidth / (levelCount / 2)) - 1;

    cout << string(spaceBefore * 2, ' ');

    for (int i = 0; i < levelCount && idx < n; ++i, ++idx) {
      cout << setw(2) << heap[idx];
      if (i < levelCount - 1)
        cout << string(spaceBetween * 2, ' ');
    }
    cout << "\n";
  }
}
void heapify(int arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;
  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    swap(arr[i], arr[largest]);
    heapify(arr, n, largest);
  }
}

void heap_sort(int arr[], int n) {
  // Step 1: Build max heap
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  printFancyHeap(arr, n);

  // Step 2: Extract max one by one
  for (int i = n - 1; i > 0; i--) {
    swap(arr[0], arr[i]); // Move max to end
    heapify(arr, i, 0);   // Restore heap
  }
}

int main() {
  int n;
  n = 10;
  int a[] = {2, 4, 5, 3, 1, 9, 6, 7, 10, 8};

  heap_sort(a, n);
  printFancyHeap(a, n);
}
