#include <iostream>
using namespace std;

void merge_sort(int a[], int n);
void merge_sorted_recursion(int a[], int l, int r);
void merge_sorted_array(int a[], int l, int m, int r);

int main() {
  int length = 10;
  int array[] = {4, 5, 3, 7, 8, 1, 2, 9, 6, 10};
  merge_sort(array, length);

  for (size_t i = 0; i < length; i++)
    cout << array[i] << " ";

  return 0;
}

void merge_sort(int a[], int length) {
  merge_sorted_recursion(a, 0, length - 1);
}

void merge_sorted_recursion(int a[], int l, int r) {
  if (l < r) {
    int mid = l + (r - l) / 2;

    merge_sorted_recursion(a, l, mid);
    merge_sorted_recursion(a, mid + 1, r);

    merge_sorted_array(a, l, mid, r);
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

  //                  i
  //  left_array = 4 9 12
  //                 j
  // right_array = 5 8 14
  //                   k
  //           a = 4 5

  for (int i = 0, j = 0, k = l; k <= r; k++) {
    // 當 i 已經到了 left_array 的尾端( i == left_length )，就只要 copy
    // right_array[j] 到 a[k] 就好
    //
    //    ^
    //    |
    //    |
    //
    if (i < left_length &&
        (j >= right_length || left_array[i] <= right_array[j])) {
      a[k] = left_array[i];
      i++;
    } else {
      a[k] = right_array[j];
      j++;
    }
  }
}
