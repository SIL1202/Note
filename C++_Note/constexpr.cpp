#include <iostream>
using namespace std;

constexpr int factorial(int n) { return n <= 1 ? 1 : n + factorial(n - 1); }
int main() {
  constexpr int x = 5;
  constexpr int y = x + 5;
  cout << "y = " << y << endl;

  cout << factorial(5);
  return 0;
}
