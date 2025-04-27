#include <animal.h>
#include <iostream>

void Cat::speak() { std::cout << "Meow!\n"; }

void Dog::speak() { std::cout << "Woof!\n"; }

int main() {
  Cat::speak();
  Dog::speak();

  return 0;
}
