#include <iostream>
#include <vector>

using namespace std;

void swap(int &, int &);
void quickSort(vector<int> &, int, int, int);
int quick_partition(vector<int> &, int, int);

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++)
    arr[i] = n - i;

  quickSort(arr, 0, arr.size() - 1, 0);

  for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
  return 0;
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

// QuickSort
void quickSort(vector<int> &array, int low, int high, int depth) {
  if (low >= high) {
    return;
  }

  int pivot = quick_partition(array, low, high);

  // 記錄當前範圍內的數組、pivot 位置、遞迴深度
  vector<int> temp(array.begin() + low, array.begin() + high + 1);

  quickSort(array, low, pivot - 1, depth + 1);
  quickSort(array, pivot + 1, high, depth + 1);
}

// Partition
int quick_partition(vector<int> &array, int low, int high) {
  int pivot_value = array[high];
  int i = low;
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot_value) {
      swap(array[i], array[j]);
      i++;
    }
  }
  swap(array[i], array[high]);
  return i;
}

/*

6 3 7 5 1 2 [4]
             |
     3 1 [2] 4 6 7 [5]
          |         |
        1 2 3     4 5 6 7

depth
space
pivot

*/
