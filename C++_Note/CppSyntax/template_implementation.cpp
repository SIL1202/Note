#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>

class Memory {
private:
  T **matrix;
  int rows, cols;

public:
  Memory(int m, int n) : rows(m), cols(n) { allocMatrix(m, n); }

  void allocMatrix(int m, int n) {
    rows = m;
    cols = n;
    matrix = new T *[m];
    T *all = new T[m * n];

    for (int i = 0; i < m; i++)
      matrix[i] = &all[i * n];
  }

  void setValue(int i, int j, T value) { matrix[i][j] = value; }

  T getValue(int i, int j) { return matrix[i][j]; }

  void printMatrix() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        cout << getValue(i, j) << " ";
      }
      cout << "\n";
    }
  }

  ~Memory() {
    delete[] matrix[0];
    delete[] matrix;
  }
};

template <typename U = int> class MyClass {
private:
  U data;

public:
  MyClass() {}
  MyClass(U data) : data(data) {}
};

template <typename M, typename N> class MyPair {
  M first;
  N second;

public:
  MyPair() {}
  MyPair(M a, N b) : first(a), second(b) {}
  void setPair(M a, N b) {
    first = a;
    second = b;
  }
  void printPair() { cout << first << " " << second; }
};

template <typename T, int size> class Array {
  T arr[size];

public:
  T &operator[](int index) { return arr[index]; }

  void print() {
    for (int i = 0; i < size; i++)
      cout << arr[i] << " ";
    cout << endl;
  }
};

template <typename T, T *val> class pointWrapper {
public:
  void setValue(int Val) { *val = Val; }

  void printValue() { cout << "value = " << *val << endl; }
};
int MyVal = 45;

int main() {
  // pointWrapper
  pointWrapper<int, &MyVal> wrapper;
  wrapper.printValue();
  wrapper.setValue(100);
  wrapper.printValue();

  // Array
  Array<int, 5> array;
  for (int i = 0; i < 5; i++)
    array[i] = i + 1;
  array.print();

  // MyClass
  MyClass<> obj1(10);
  MyClass<double> obj2(3.14);

  // MyPair
  const int numPairs = 5;
  MyPair<int, double> pairs[numPairs];
  for (int i = 0; i < numPairs; i++) {
    pairs[i].setPair(i + 1, i * 1.5);
    pairs[i].printPair();
    cout << "\n";
  }

  // Memory
  Memory<int> memoryINT(3, 3);
  Memory<float> memoryFLOAT(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      memoryINT.setValue(i, j, i * 3.1 + j);
      memoryFLOAT.setValue(i, j, i * 3.1 + j);
    }
  }
  memoryINT.printMatrix();
  memoryFLOAT.printMatrix();
  return 0;
}
