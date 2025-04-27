#include <iostream>
#include <memory>

template <typename T> class Myclass {
private:
  T value;

public:
  Myclass() {}
  Myclass(T v) : value(v) {}

  void produce() { std::cout << value << std::endl; }

  friend std::istream &operator>>(std::istream &in, Myclass &obj1);

  friend std::ostream &operator<<(std::ostream &out, Myclass &obj2);
};

template <typename T>
std::istream &operator>>(std::istream &in, Myclass<T> &obj1) {
  in >> obj1.value;
  return in;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Myclass<T> &obj2) {
  out << obj2.value;
  return out;
}

int main() {
  auto ptr = std::make_unique<Myclass<int>>(10); // specific object
  // make_unique will automatically manage the memory
  ptr->produce();

  std::cout << "enter 10 values: ";
  auto arr = std::make_unique<Myclass<char>[]>(10);
  for (int i = 0; i < 10; i++) {
    std::cin >> arr[i];
  }

  std::cout << std::endl;
  std::cout << "your values:\n";

  for (int i = 0; i < 10; i++) {
    std::cout << arr[i];
  }

  std::cout << std::endl;
  return 0;
}
