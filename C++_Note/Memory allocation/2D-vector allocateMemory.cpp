#include <iostream>
#include <vector>

std::vector<std::vector<int>> allocateMemory(int r, int c) {
  return std::vector<std::vector<int>>(r, std::vector<int>(c));
}

int main() {
  int rows, cols;
  std::cin >> rows >> cols;

  auto matrix = allocateMemory(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = i * cols + j;
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
