#include "other.hpp"
#include <iostream>

////////////////////////////////////////
// #1 Local static variable in function
////////////////////////////////////////

// This function uses a local static variable `a`.
// It is initialized only once and retains its value across function calls.
void foo() {
  static int a = 0; // Initialized once, keeps value between calls
  a++;
  std::cout << "a = " << a << std::endl;
}

////////////////////////////////////////
// #2 Global static variable with initializer function
////////////////////////////////////////

// This function will be used to initialize the global static variable `b`.
// It will run only once before `main()` starts.
int initB() {
  std::cout << "Initializing b...\n";
  return 123;
}

// Global static variable initialized via a function.
// This happens before `main()` begins.
static int b = initB();

////////////////////////////////////////
// #3 class with a static member variable and method
////////////////////////////////////////

class Tool {
public:
  // Static member variable `c` is shared by all instances of Tool.
  static int c;

  // Member function that sets the static variable `c`
  void foo() { c = 9; }
};

// Static member variable must be defined outside the class.
int Tool::c = 0;

////////////////////////////////////////
// #4 class with a static member function and method
////////////////////////////////////////
/*
class Tool2 {
public:
  static int count;
  static void foo() { count++; }
};

// Static member variable must be defined outside the class
int Tool2::count = 0; */

////////////////////////////////////////
// main function
////////////////////////////////////////

int main() {
  // Print the value of global static variable `b`
  std::cout << "b = " << b << '\n'; // Output: b = 123

  std::cout << '\n';

  // Call foo() 10 times, observe static variable `a` increment
  for (int i = 0; i < 10; i++)
    foo();

  // Show the value of static class member `c`
  std::cout << "c = " << Tool::c << '\n'; // Initially 0

  Tool t;
  t.foo(); // Sets static member `c` to 9

  std::cout << "c = " << Tool::c << '\n'; // Now 9

  for (int i = 0; i < 10; i++)
    Tool2::foo();

  std::cout << Tool2::count << '\n';

  // access other in namespace from outer file
  space::other();
  return 0;
}
