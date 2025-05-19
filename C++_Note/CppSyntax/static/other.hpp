#pragma once
#include <iostream>

class Tool2 {
public:
  static int count;
  static void foo() { count++; }
};

// replace static with namespace
namespace space{
  // declare other in namespace
  void other();
}
