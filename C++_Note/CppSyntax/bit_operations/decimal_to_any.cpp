#include <bitset>
#include <iostream>
#include <string>

int main() {
  int decimal_number;
  std::cin >> decimal_number;

  std::bitset<8> binary(decimal_number); // convert decimal to binary.
  std::cout << "binary number = " << binary << std::endl;
  std::cout << "There are " << binary.count()
            << " ones in it.\n"; // out put how many ones in binary number.

  int octal_value;
  std::cin >> octal_value;

  // convert octal_value to decimal_value and convert it to binary number
  int decimal_value =
      std::stoi(std::to_string(octal_value), nullptr,
                8); // 8 represent to octal, 16 represent to hexa and so no...
  std::bitset<16> binary2(
      decimal_value); // 16 represent to 16 bits binary_value.
  std::cout << "convert octal_value: " << octal_value << " to "
            << "decimal_value: " << decimal_value
            << " , then to binary value: " << binary2 << std::endl;
}
