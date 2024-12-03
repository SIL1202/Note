#include <iostream>

using namespace std;

void insertionSort(int arr[], int n);
void print(int arr[], int n);

int main() {
  int arr[8] = {4, 6, 7, 8, 5, 3, 1, 0};
  insertionSort(arr, 8);
  print(arr, 8);

  return 0;
}

void insertionSort(int arr[], int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void print(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}
