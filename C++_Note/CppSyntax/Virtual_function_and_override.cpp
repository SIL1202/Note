#include <iostream>

using namespace std;
class Base {
public:
  virtual void speak() { std::cout << "Base speaking\n"; }
};

class Derived : public Base {
public:
  // override 可以檢查當derived class 裡的virtual function 是否被改變
  void speak(int volume) override { // Intention: override Base::speak
    std::cout << "Derived speaking\n";
  }
};

class Animal {
public:
  virtual void speaking() { cout << "animal speaking\n"; }
};

class Dog : public Animal {
public:
  void speaking() { cout << "woof!\n"; }
};

class Cat : public Animal {
public:
  void speaking() { cout << "Meow!\n"; }
};

int main() {
  Animal *animal = new Animal();
  animal->speaking();
  animal = new Dog();
  animal->speaking();
  animal = new Cat();
  animal->speaking();

  return 0;
}
