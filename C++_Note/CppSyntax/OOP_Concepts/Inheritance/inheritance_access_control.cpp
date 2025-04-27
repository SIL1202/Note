#include <iostream>

class Base {
private:
  int private_value_ = 0;
  // 原本 private 的成員不管用什麼形式繼承，他永遠都只能在 Dase 裡面使用

protected:
  int protected_value_ = 1;

public:
  int public_value_ = 2;
};

// 繼承的形式只能做到降級的效果，不能升級
class Derived1 : private Base {
public:
  void print() {
    std::cout << private_value_ << std::endl; // 原本就不行
    std::cout << protected_value_ << std::endl;
    std::cout << public_value_ << std::endl;
  }
};

class Derived2 : protected Base {
public:
  void print() {
    std::cout << private_value_ << std::endl; // 原本就不行
    std::cout << protected_value_ << std::endl;
    std::cout << public_value_ << std::endl;
    // 這裡讓原本是 public 的成員變成 protected 因此只能在 Base class 和 Derived
    // class 裡面使用，其他地方不行
  }
};

class Derived3 : public Base {
public:
  void print() {
    std::cout << private_value_ << std::endl; // 原本就不行
    std::cout << protected_value_ << std::endl;
    std::cout << public_value_ << std::endl;
  }
};

int main() {
  Derived1 d1;
  std::cout << d1.private_value_ << std::endl;   // 原本就不行
  std::cout << d1.protected_value_ << std::endl; // 原本就不行
  std::cout << d1.public_value_ << std::endl;    // 原本可以
  // 原本這裡是可以存取 public_value_ 的，但是現在他已經變成 private
  // 了，所以不能

  Derived2 d2;
  std::cout << d2.private_value_ << std::endl;   // 原本就不行
  std::cout << d2.protected_value_ << std::endl; // 原本就不行
  std::cout << d2.public_value_ << std::endl;    // 原本可以
  // 原本這裡是可以存取 public_value_ 的，但是現在他已經變成 protected
  // 了，所以不能

  Derived3 d3;
  std::cout << d3.private_value_ << std::endl;   // 原本就不行
  std::cout << d3.protected_value_ << std::endl; // 原本就不行
  std::cout << d3.public_value_ << std::endl;    // 仍然可以
  // 這裡依然是 public 所以可以存取
  return 0;
}
