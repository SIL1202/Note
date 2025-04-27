#include <iostream>
#include <unordered_set>

int main() {
  std::unordered_set<int> uset;
  uset.insert(10);
  uset.insert(20);
  uset.insert(10);

  std::cout << "Size: " << uset.size() << std::endl;

  if (uset.find(10) != uset.end()) {
    std::cout << "10 存在! " << std::endl;
  }
  return 0;
}
