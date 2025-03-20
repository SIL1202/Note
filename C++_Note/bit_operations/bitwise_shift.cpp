#include <iostream>

int main() {
  int x = 3;      // 00000011
  int y = x << 4; // 00110000 (3 * 2 ^ 4 = 48)
  int z = y >> 3; // 00000110 (3 / 2 ^ 3)
  std::cout << y << std::endl;
  std::cout << z << std::endl;
  return 0;
}
