#include "other.hpp"

// define static var outside class
int Tool2::count = 0;

// define other in namespace
void space::other() { std::cout << "access static other\n"; }
