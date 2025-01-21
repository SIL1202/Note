#include <iostream>

class Myclass {
public:
  int value;
  Myclass() {}
  Myclass(int v) : value(v) {}
  Myclass &operator=(const Myclass &other) {
    if (this != &other) { // 需要確保不會自我賦值，如果自我賦值的話：
      // delete data(int* data)
      // data = new int(*other.data);
      value = other.value;
    }
    return *this;
  }
  Myclass operator+(const Myclass &other) {
    // 這裡不需要返回＆（引用），因為回傳的是新創建的class type，
    // 而這個class type在函數結束時回被銷毀，返回它的引用會導致未定義行為
    // （因為引用指向已經被釋放的記憶體）。
    return Myclass(value + other.value);
  }
};

int main() {
  Myclass a(5), b(8);
  Myclass c = b;

  Myclass d = a + b;
  std::cout << c.value << std::endl;
  std::cout << d.value << std::endl;
  return 0;
}
