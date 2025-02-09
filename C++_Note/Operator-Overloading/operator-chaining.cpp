#include <iostream>
template <class T> class Node {
public:
  Node() { data = new T; }
  Node(T d) { data = new T(d); }
  ~Node() { delete data; }

  Node &operator=(const T &d) {
    *data = d;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &out, const Node<T> &d) {
    out << (*d.data);
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Node<T> &d) {
    in >> (*d.data);
    return in;
  }

  void setData(T d) { (*data) = d; }

  T &getData() const { return *data; }

protected:
  T *data; // ***這裡用指標是為了可以存取Ａ類型***
};

class A {
public:
  const int x;
  A(int v) : x(v) {}

  friend std::ostream &operator<<(std::ostream &out, const A &other) {
    out << other.x;
    return out;
  }
};

int main() {

  Node<A> n1(A(10));
  Node<A> n2(A(20));

  std::cout << n1;
}

// 總結執行順序:
//
// 1.std::cout << n1;
//   呼叫 Node<A> 的 operator<<
// 2.out << (*n1.data);
//   *n1.data 會變成 A(10)
// 3.std::cout << A(10);
//   呼叫 A 的 operator<<
// 4.std::cout << 10;
//   輸出 10
