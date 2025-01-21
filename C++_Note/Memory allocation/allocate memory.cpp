
int **allocateMemory(int r, int c) { // nonconsecutive memory
  int **maze = new int *[r];

  for (int i = 0; i < r; i++) {
    maze[i] = new int[c];
  }
  return maze;
}

void deallocateMemory(int **maze, int r, int c) {
  for (int i = 0; i < r; i++) {
    delete[] maze[i];
  }
  delete[] maze;
}

int **consecutiveMemory(int r, int c) { // consecutive memory
  int *data = new int[r * c];
  int **maze = new int *[r];

  for (int i = 0; i < r; i++) {
    maze[i] = data + i * c;
  }
  return maze;
}

void deallocateMemory2(int **maze2) { // deallocate memory
  if (maze2 != nullptr) {
    delete[] maze2[0];
    delete[] maze2;
  }
}

int main() {
  int *One_Object = new int; // 建立單一物件記憶體
  // int *One_Object = new int(5)  ==> asign 5 for it.
  delete One_Object; // 非陣列的釋放記憶體

  int *array_Object = new int[10];
  delete[] array_Object; // 陣列釋放記憶體

  int rows, cols;
  std::cin >> rows >> cols;
  int **maze = allocateMemory(rows, cols); // nonconsecutive memory
  deallocateMemory(maze, rows, cols);
  int **maze2 = consecutiveMemory(rows, cols);
  deallocateMemory2(maze2);
  return 0;
}
