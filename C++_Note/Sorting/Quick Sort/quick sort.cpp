#include <iostream>
#include <vector>

using namespace std;

struct QuickSortInfo {
  vector<int> array;
  int pivotIndex;
  int depth;
};

void swap(int &, int &);
void quickSort(vector<int> &, int, int, vector<QuickSortInfo> &, int);
int quick_partition(vector<int> &, int, int);
void print(const vector<QuickSortInfo> &);

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++)
    cin >> arr[i];

  vector<QuickSortInfo> info;
  quickSort(arr, 0, arr.size() - 1, info, 0);

  for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
  // print(info);
  return 0;
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

// QuickSort
void quickSort(vector<int> &array, int low, int high,
               vector<QuickSortInfo> &info, int depth) {
  if (low >= high) {
    return;
  }

  int pivot = quick_partition(array, low, high);

  // 記錄當前範圍內的數組、pivot 位置、遞迴深度
  vector<int> temp(array.begin() + low, array.begin() + high + 1);
  info.push_back({temp, pivot - low, depth});

  quickSort(array, low, pivot - 1, info, depth + 1);
  quickSort(array, pivot + 1, high, info, depth + 1);
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

// Print function
void print(const vector<QuickSortInfo> &info) {
  for (const auto &entry : info) {
    // 縮排，根據 depth 決定空格數
    for (int i = 0; i < entry.depth * 5; i++)
      cout << " ";

    // 印出當前快排狀態，標示 pivot
    for (int i = 0; i < entry.array.size(); i++) {
      if (i == entry.pivotIndex)
        cout << "[";
      cout << entry.array[i];
      if (i == entry.pivotIndex)
        cout << "]";
      cout << " ";
    }
    cout << endl;
  }
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
