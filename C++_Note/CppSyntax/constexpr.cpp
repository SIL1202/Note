#include <iostream>
using namespace std;

// The primary purpose of constexpr is to allow computations to occur during
// compilation, rather than at runtime. This can improve program performance by
// reducing runtime overhead.
constexpr int factorial(int n) { return n <= 1 ? 1 : n + factorial(n - 1); }
int main() {
  constexpr int x = 5;
  constexpr int y = x + 5;
  cout << "y = " << y << endl;

  cout << factorial(5);
  return 0;
}
