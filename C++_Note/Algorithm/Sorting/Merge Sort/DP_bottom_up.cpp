#include <iostream>
using namespace std;

void merge_sort(int a[], int n);
void merge_sorted_array(int a[], int l, int m, int r);

int main() {
  int length = 10;
  int array[] = {4, 5, 3, 7, 8, 1, 2, 9, 6, 10};
  merge_sort(array, length);

  for (int i = 0; i < length; i++)
    cout << array[i] << " ";

  return 0;
}

#include <iomanip> // for setw

void merge_sort(int a[], int n) {
  for (int size = 1; size < n; size *= 2) {
    cout << "=== Merging size: " << size << " ===" << endl;

    for (int left = 0; left < n - size; left += 2 * size) {
      int mid = left + size - 1;
      int right = min(left + 2 * size - 1, n - 1);

      merge_sorted_array(a, left, mid, right);

      // 印出目前陣列狀態
      cout << "After merging [" << left << "," << right << "]: ";
      for (int i = 0; i < n; ++i)
        cout << setw(2) << a[i] << " ";
      cout << endl;
    }
  }
}

void merge_sorted_array(int a[], int l, int m, int r) {
  int left_length = m - l + 1;
  int right_length = r - m;

  int left_array[left_length];
  int right_array[right_length];

  for (int i = 0; i < left_length; i++)
    left_array[i] = a[l + i];
  for (int i = 0; i < right_length; i++)
    right_array[i] = a[m + 1 + i];

  for (int i = 0, j = 0, k = l; k <= r; k++) {
    if (i < left_length &&
        (j >= right_length || left_array[i] <= right_array[j])) {
      a[k] = left_array[i++];
    } else {
      a[k] = right_array[j++];
    }
  }
}
