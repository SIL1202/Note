#include <algorithm>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>
using namespace std::chrono;

void bubble_sort(std::vector<int> &);
int main() {
  // initialize two array.
  std::vector<int> array(10000);
  std::vector<int> array1(10000);
  for (int i = 0; i < 10000; i++)
    array[i] = 10000 - i;
  for (int i = 0; i < 10000; i++)
    array1[i] = 10000 - i;

  auto start = high_resolution_clock::now(); // toggle starting point.
  std::sort(array.begin(), array.end());     // first sorting method
  auto end = high_resolution_clock::now();   // toggle ending point.

  auto duration =
      duration_cast<microseconds>(end - start); // cast unit to microseconds.
  std::cout << duration.count() << std::endl;   // output first duration.

  start = high_resolution_clock::now(); // toggle second starting point.
  bubble_sort(array1);                  // second sorting method
  end = high_resolution_clock::now();   // toggle second ending point

  duration = duration_cast<microseconds>(end - start);
  std::cout << duration.count() << std::endl; // output second duration
  return 0;
}

// bubble_sort
void bubble_sort(std::vector<int> &a) {
  for (int i = 0; i < a.size() - 1; i++) {
    for (int j = 1; j < a.size() - i; j++) {
      if (a[j] < a[j - 1])
        std::swap(a[j], a[j - 1]);
    }
  }
}
