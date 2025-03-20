#include <bitset>
#include <iostream>

// declaration
void swap(int &, int &);
int countBits(int);
bool isPowerOfTwo(int);

int main() {
  int x = 3;      // 00000011
  int y = x << 4; // 00110000 (3 * 2 ^ 4 = 48)
  int z = y >> 3; // 00000110 (3 / 2 ^ 3)
                  // 正數相當於整除
  int a = z >> 2; // 00000001 ( 6 / 2 ^ 2)
  std::cout << y << std::endl;
  std::cout << z << std::endl;
  std::cout << a << std::endl;

  // chech if the number is the power of two.
  std::cout << "6" << (isPowerOfTwo(6) ? " is " : " is not ")
            << "the power of two\n";
  std::cout << "4" << (isPowerOfTwo(4) ? " is " : " is not ")
            << "the power of two\n";
  std::cout << "3" << (isPowerOfTwo(3) ? " is " : " is not ")
            << "the power of two\n";

  // caculate how many one within the number
  std::bitset<8> binary(5);
  std::cout << "5(" << binary << ") has " << binary.count() << "'s 1. \n"
            << std::endl;

  // swap
  int A = 6;
  int B = 5;
  swap(A, B);
  std::cout << "A = " << A << std::endl;
  std::cout << "B = " << B << std::endl;

  // set a bit
  int C = 5;
  int pos = 1;
  std::bitset<4> binary1(C);
  C |= (1 << pos);
  std::bitset<4> binary2(C);
  std::cout << binary1 << " -> " << binary2 << std::endl;

  // clear a bit
  C &= ~(1 << pos);
  binary1.set();
  std::cout << binary2 << " -> " << binary1 << std::endl;
  return 0;
}

// use XOR to implement swap function.
void swap(int &a, int &b) { // XOR swap
  a ^= b;                   // a = a ^ b
  b ^= a;                   // b = a ^ b = (a ^ b) ^ b = a ^ 0 = a
  a ^= b;                   // a = a ^ b = (a ^ b) ^ a = b ^ 0 = b
}

int countBits(int x) {
  int count = 0;
  while (x) {
    x &= (x - 1);
    count++;
  }
  return count;
}

// x - 1 會把最低位的 1 變成 0，如果 x 是 2 的次方，那麼 x & (x - 1) 必定為 0。
bool isPowerOfTwo(int x) { return (x > 0) && ((x & (x - 1)) == 0); }

// 5(00000101)
// 1 << 2 (1 * 2 ^ 2) == 4(00000100)
// 1 << 1 (1 * 2 ^ 1) == 2(00000010)
