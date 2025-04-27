#include <cstring> // For strcmp
#include <iostream>

using namespace std;

#define SIZE 100

class Node {
public:
  Node(int data) : data(data), next(nullptr), prev(nullptr) {}
  Node *next;
  Node *prev;
  int data;
};

class Circular_Deque {
public:
  Circular_Deque() : front(nullptr), rear(nullptr), count(0) {
    arr = new int[SIZE];
  }
  ~Circular_Deque() { delete arr; }

  int enqueueFront(int data) {
    if (count == SIZE)
      return -1;

    Node *newNode = new Node(data);
    if (count == 0)
      front = rear = newNode;
    else {
      newNode->next = front;
      front->prev = newNode;
      front = newNode;
    }

    count++;
    return 1;
  }

  int enqueueRear(int data) {
    if (count == SIZE)
      return -1;

    Node *newNode = new Node(data);
    if (count == 0)
      front = rear = newNode;
    else {
      rear->next = newNode;
      newNode->prev = rear;
      rear = newNode;
    }

    count++;
    return 1;
  }

  int *dequeueFront() {
    if (count == 0)
      return nullptr;

    int *result = new int(front->data);
    Node *temp = front;
    front = front->next;
    delete temp;

    if (front)
      front->prev = nullptr;
    else
      rear = nullptr;

    count--;
    return result;
  }

  int *dequeueRear() {
    if (count == 0)
      return nullptr;

    int *result = new int(rear->data);
    Node *temp = rear;
    rear = rear->prev;
    delete temp;

    if (rear)
      rear->next = nullptr;
    else
      front = nullptr;

    count--;
    return result;
  }

  void print() {
    Node *temp = front;
    while (temp) {
      cout << temp->data << " ";
      temp = temp->next;
    }
    cout << endl;
  }

private:
  Node *front, *rear;
  int *arr, count;
};

int main() {
  Circular_Deque *deque = new Circular_Deque();
  char command[50];

  while (true) {
    cout << "Input command: ";
    cin >> command; // Capture the command

    int data;

    if (strcmp(command, "exit") == 0) {
      break;
    } else if (strcmp(command, "enqueueFront") == 0) {
      cin >> data;
      if (deque->enqueueFront(data) == 1) {
        cout << "Successfully enqueued data " << data << " into front deque.\n";
      } else {
        cout << "Fail to enqueue data into front deque.\n";
      }
    } else if (strcmp(command, "enqueueRear") == 0) {
      cin >> data;
      if (deque->enqueueRear(data) == 1) {
        cout << "Successfully enqueued data " << data << " into rear deque.\n";
      } else {
        cout << "Fail to enqueue data into rear deque.\n";
      }
    } else if (strcmp(command, "dequeueFront") == 0) {
      int *deqData = deque->dequeueFront();
      if (deqData) {
        cout << "Successfully dequeued data " << *deqData
             << " from front deque.\n";
        delete deqData;
      } else {
        cout << "Fail to dequeue data from front deque.\n";
      }
    } else if (strcmp(command, "dequeueRear") == 0) {
      int *deqData = deque->dequeueRear();
      if (deqData) {
        cout << "Successfully dequeued data " << *deqData
             << " from rear deque.\n";
        delete deqData;
      } else {
        cout << "Fail to dequeue data from rear deque.\n";
      }
    } else if (strcmp(command, "print") == 0) {
      deque->print();
    } else {
      cout << "Unknown command!\n";
    }
  }

  delete deque;
  return 0;
}
