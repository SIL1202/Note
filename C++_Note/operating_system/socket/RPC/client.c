// compiled with: gcc -o client client.c
// This is a simple client that connects to a registry to find a service
// and then calls that service with two numbers.
// It assumes the registry is running on localhost at port 8888 and the service
// is named "add".
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REG_PORT 8888
#define BUFSZ 256

static int connect_to(const char *ip, int port) {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in a = {0};
  a.sin_family = AF_INET;
  a.sin_port = htons(port);
  inet_pton(AF_INET, ip, &a.sin_addr);
  if (connect(s, (struct sockaddr *)&a, sizeof(a)) < 0) {
    perror("connect");
    exit(1);
  }
  return s;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s a b\n", argv[0]);
    return 1;
  }
  long a = atol(argv[1]), b = atol(argv[2]);

  // (1) 向 registry 查詢
  int reg = connect_to("127.0.0.1", REG_PORT);
  dprintf(reg, "LOOKUP add\n");
  char line[BUFSZ] = {0};
  read(reg, line, sizeof(line));
  close(reg);

  int port = 0;
  if (sscanf(line, "PORT %d", &port) != 1) {
    fprintf(stderr, "service not found\n");
    return 1;
  }

  // (2) 連真正服務並呼叫
  int s = connect_to("127.0.0.1", port);
  dprintf(s, "ADD %ld %ld\n", a, b);
  char out[BUFSZ] = {0};
  read(s, out, sizeof(out));
  close(s);
  printf("%s", out);
  return 0;
}
