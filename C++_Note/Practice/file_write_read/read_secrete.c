#include <stdio.h>
#include <stdlib.h>

int main() {
  const char *filename = "/tmp/secrete.txt";
  char content[1000];

  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printf("file doesn't exist!\n");
    exit(1);
  }

  fgets(content, 10, f);
  printf("password: %s\n", content);
  fclose(f);
  return 0;
}
