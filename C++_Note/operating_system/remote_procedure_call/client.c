// gcc client.c -o client
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 9000
#define BUFSZ 1024

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s a b\n", argv[0]);
    return 1;
  }
  long a = atol(argv[1]), b = atol(argv[2]);

  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    return 1;
  }

  char req[64];
  snprintf(req, sizeof(req), "ADD %ld %ld\n", a, b);
  send(s, req, strlen(req), 0);

  char buf[BUFSZ] = {0};
  ssize_t n = recv(s, buf, sizeof(buf) - 1, 0);
  if (n > 0)
    printf("%s", buf);

  close(s);
  return 0;
}
