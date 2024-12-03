#include <iostream>
using namespace std;

template <typename T> class example {
public:
  void print(T val) { cout << "value = " << val << endl; }
};

template <> class example<char> {
public:
  void display(char val) {
    cout << "char value = " << static_cast<int>(val) << endl;
  }
};
int main() {
  example<int> ex1;
  ex1.print(10);
  example<double> ex2;
  ex2.print(9.8);
  example<char> ex3;
  ex3.display('A');

  return 0;
}
