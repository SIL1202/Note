#include <iostream>

using namespace std;

int main() {
  int array[10] = {98, 74, 77, 34, 44, 26, 37, 18, 93, 10};
  for (int first = 0; first < 10; first++) {

    int minIndex = first;
    for (int j = first + 1; j < 10; j++) {
      if (array[j] < array[minIndex]) {
        minIndex = j;
      }
    }
    int temp = array[minIndex];
    array[minIndex] = array[first];
    array[first] = temp;
  }
  for (int i = 0; i < 10; i++)
    cout << array[i] << " ";
  return 0;
}
