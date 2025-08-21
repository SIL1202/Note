#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  dprintf(fd, "This is a test file the number is %d", 123);
  close(fd);

  return 0;
}
