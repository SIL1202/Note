#include <stdio.h>

int main() {

  const char *filename = "/tmp/secrete.txt";
  const char password[] = "1202";
  FILE *f = fopen(filename, "w");

  fprintf(f, password);

  fclose(f);
  return 0;
}
