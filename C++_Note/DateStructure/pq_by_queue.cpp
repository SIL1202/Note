#include <iostream>
#include <queue>

const int MAX = 100;

template <class T> class Priority_queue {
private:
  std::queue<T> q;
  T buffer[MAX];
  int size = 0;
  int (*cmp)(T a, T b);

public:
  Priority_queue<T>(int (*cmpFunc)(T, T)) : cmp(cmpFunc) {}

  void enqueue(T value) {
    int i = size - 1;
    while (i >= 0 && cmp(value, buffer[i]) < 0) {
      buffer[i + 1] = buffer[i];
      i--;
    }
    buffer[i + 1] = value;
    size++;

    std::queue<T> new_q;
    for (int j = 0; j < size; j++)
      new_q.push(buffer[j]);
    q = new_q;
  }

  T dequeue() {
    if (q.empty()) {
      std::cout << "empty queue\n";
      return T(); // 回傳預設值（0.0、""...）
    }
    T res = q.front();
    q.pop();
    size--;
    return res;
  }

  void print() {
    while (size > 0) {
      T res = dequeue();
      std::cout << res << '\n';
    }
  }
};

template <typename T> int cmpGenericMin(T a, T b) {
  return (a < b) ? -1 : (a > b) ? 1 : 0;
}

template <typename T> int cmpGenericMax(T a, T b) {
  return (a > b) ? -1 : (a < b) ? 1 : 0;
}

int main() {
  Priority_queue<double> pq(cmpGenericMin<double>); // min heap
  pq.enqueue(9.3);
  pq.enqueue(8.2);
  pq.enqueue(3.5);
  pq.enqueue(4);
  pq.print();

  std::cout << '\n';

  Priority_queue<int> pq2(cmpGenericMax<int>); // max heap
  pq2.enqueue(9);
  pq2.enqueue(8);
  pq2.enqueue(3);
  pq2.enqueue(4);
  pq2.print();
  return 0;
}
