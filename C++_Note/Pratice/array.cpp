#include <iostream>

int main() {
  int arr[3] = {1, 2};

  std::cout << "arr = " << arr << std::endl;
  std::cout << "arr[0] = " << arr[0] << std::endl;
  std::cout << "arr[1] = " << *(arr + 1) << std::endl;

  int *a;
  *a = 3;
  *(a + 1) = 4;
  std::cout << "a[0] = " << a[0] << std::endl;
  std::cout << "a[1] = " << *(a + 1) << std::endl;

  int *b = &arr[1];
  *b = 3;
  std::cout << "arr[0] = " << arr[0] << std::endl;
  std::cout << "*b = arr[1] = " << arr[1] << std::endl;
  *(b + 1) = 7;
  std::cout << "arr[2] = " << arr[2] << std::endl;

  int *p = arr;
  p[2] = 3;
  int **p2 = &p;

  std::cout << "p2[2] = " << p[2] << std::endl;
  return 0;
}
