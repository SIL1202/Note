#include <stdio.h>

void print(const void *a, const int n, const char type) {
  int first = 1;
  for (int i = 0; i < n; i++) {
    if (!first)
      printf(" ");
    else
      first = 0;

    switch (type) {
    case 'c':
      printf("%c", ((const char *)a)[i]);
      break;
    case 'f':
      printf("%.1f", ((const float *)a)[i]);
      break;
    case 'd':
      printf("%.1f", ((const double *)a)[i]);
      break;
    default:
      fprintf(stderr, "[warning] Unsupported type: %c", type);
      return;
    }
  }
  printf("\n");
}

int main() {
  const char s[] = {'a', 'b', 'c'};           // define character array
  const float f[] = {0.1f, 0.2f, 0.3f, 0.4f}; // define float array

  print(s, sizeof(s) / sizeof(char), 'c');
  print(f, sizeof(f) / sizeof(float), 'f');
}
