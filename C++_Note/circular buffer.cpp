#include <iostream>
using namespace std;

#define SIZE 100

class CircularBuffer {
public:
  CircularBuffer() : front(0), rear(0), count(0) {}

  int add(int data) {
    // If buffer is full, overwrite the oldest data
    if (count == SIZE) {
      front =
          (front + 1) % SIZE; // Move front forward to overwrite the oldest data
    } else {
      count++;
    }

    this->data[rear] = data;
    rear = (rear + 1) % SIZE;
    return 1;
  }

  int *remove() {
    if (count == 0)
      return NULL;

    int *temp = &data[front];
    front = (front + 1) % SIZE;
    count--;
    return temp;
  }

  void print() {
    int temp = front;
    for (int i = 0; i < count; i++) {
      cout << data[temp] << " ";
      temp = (temp + 1) % SIZE;
    }
    cout << endl;
  }

private:
  int data[SIZE];
  int front, rear;
  int count;
};

int main() {
  CircularBuffer *buffer = new CircularBuffer();
  char command[50];

  while (1) {
    cin >> command;
    if (strcmp(command, "exit") == 0)
      break;
    else if (strcmp(command, "add") == 0) {
      cout << "Input an integer number: ";
      int data;
      cin >> data;
      if (buffer->add(data) == 1)
        cout << "Successfully added data " << data << " into buffer.\n";
      else
        cout << "Failed to add data into buffer.\n";
    } else if (strcmp(command, "remove") == 0) {
      int *temp = buffer->remove();
      if (temp == NULL)
        cout << "Fail to remove data from buffer.\n";
      else
        cout << "Successfully removed data " << *temp << " from buffer.\n";
    } else if (strcmp(command, "print") == 0) {
      buffer->print();
    }
  }
  delete buffer; // Don't forget to free memory
  return 0;
}
