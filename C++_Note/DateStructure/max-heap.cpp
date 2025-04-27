#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>
template <class T> class MaxHeap {
public:
  // Constructing a empty heap.
  MaxHeap() {}
  // To add an element to the heap.
  void insert(T element) {
    data.push_back(element);
    heapifyUp(data.size() - 1);
  }
  // To remove the root element in the heap and return it.
  T extract() {
    if (data.empty())
      throw std::out_of_range("Heap is empty.");

    T root = data[0];
    data[0] = data.back(); // extract the max element
    data.pop_back();
    heapifyDown(0);
  }
  // Return the number of element int the heap.
  int count() { return data.size(); }

private:
  std::vector<T> data;

  void heapifyUp(int index) {
    while (index > 0) {
      int parent = (index - 1) / 2;
      if (data[index] <= data[parent])
        break;
      std::swap(data[index], data[parent]);
      index = parent;
    }
  }

  void heapifyDown(int index) {
    while (1) {
      int size = data.size();
      int left = index * 2 + 1;
      int right = index * 2 + 2;
      int largest = index;

      if (left < size && data[left] > data[largest])
        largest = left;
      if (right < size && data[right] > data[largest])
        largest = right;
      if (largest == index)
        break;

      std::swap(data[index], data[largest]);
      index = largest;
    }
  }
};
