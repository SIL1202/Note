#include <iostream>

template <typename T> T sum(T value) { return value; } // for only one parameter

template <typename T, typename... Args>
T sum(const T &first, const Args &...args) {
  return first + sum(args...);
}

int main() {
  std::cout << sum(0) << std::endl;
  std::cout << sum(1, 2, 3) << std::endl;
  std::cout << sum(1, 2, 3, 4, 5) << std::endl;
  return 0;
}
