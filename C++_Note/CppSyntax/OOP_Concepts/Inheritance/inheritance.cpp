#include <iostream>

using namespace std;

class Rectangle {
public:
  Rectangle(double l, double m) : length(l), width(m) {}
  double getArea() { return length * width; }

  double getPerimeter() { return 2 * (length + width); }

  void display() {
    cout << "length = " << length << endl
         << "width = " << width << endl
         << "area = " << getArea() << endl
         << "perimeter = " << getPerimeter() << endl;
  }

protected: // Can be accessed within the same class and in derived class.
  double length, width;
};

class Square : public Rectangle {
public:
  Square(double side) : Rectangle(side, side) {}

  void display() {
    cout << "\nlength = " << length << endl
         << "area = " << getArea() << endl
         << "perimeter = " << getPerimeter() << endl;
  }
};

int main() {
  Rectangle rectangle(4, 5);
  Square square(4);
  rectangle.display();
  square.display();
  return 0;
}
