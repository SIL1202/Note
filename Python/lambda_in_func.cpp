#include <functional>
#include <iostream>
using namespace std;

function<int(int)> foo(int n) {
  return [=](int x) { return x * n; };
}

int main() {
  int n;
  cin >> n;
  function<int(int)> foo2 = foo(n);
  cout << foo2(n) << '\n';

  return 0;
}
