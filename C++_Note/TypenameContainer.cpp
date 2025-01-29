#include <iostream>

template <typename Container> class BackInserter {
private:
  Container &container;

public:
  BackInserter(Container &c) : container(c) {}
  void insert(const typename Container::value_type &value) {
    container.push_back(value);
  }
};

int main() {
  std::vector<int> vec;
  BackInserter<std::vector<int>> inserter(vec);
  inserter.insert(2);
  inserter.insert(3);

  for (const auto &v : vec) {
    std::cout << v << std::endl;
  }
  return 0;
}
