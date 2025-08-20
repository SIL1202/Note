#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSZ 256
#define REG_PORT 8888
long func(const long a, const long b) { return a * b; }

int main() {
  // (a) 綁 0 由 OS 配一個臨時埠
  int srv = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in a = {0};
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  a.sin_port = htons(0);
  if (bind(srv, (struct sockaddr *)&a, sizeof(a)) < 0) {
    perror("bind");
    exit(1);
  }
  if (listen(srv, 8) < 0) {
    perror("listen");
    exit(1);
  }

  // Get the port number assigned by the OS
  socklen_t len = sizeof(a);
  int port = ntohs(a.sin_port);
  if (getsockname(srv, (struct sockaddr *)&a, &len) < 0) {
    perror("getsockname");
    exit(1);
  }
  printf("service 'add' on port %d\n", port);

  // (b) 向 registry 註冊
  int r = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ra = {0};
  ra.sin_family = AF_INET;
  ra.sin_port = htons(REG_PORT);
  inet_pton(AF_INET, "127.0.0.1", &ra.sin_addr);

  for (;;) {
    int cli = accept(srv, NULL, NULL);
    if (cli < 0) {
      perror("accept");
      continue;
    }

    char buf[BUFSZ] = {0};
    ssize_t n = recv(cli, buf, sizeof(buf) - 1, 0);
    if (n <= 0) {
      close(cli);
      continue;
    }

    long a, b;
    if (sscanf(buf, "ADD %ld %ld", &a, &b) == 2) {
      char out[64];
      snprintf(out, sizeof(out), "RESULT %ld\n", func(a, b));
      send(cli, out, strlen(out), 0);
    } else {
      const char *err = "ERROR bad_request\n";
      send(cli, err, strlen(err), 0);
    }
    close(cli);
  }
  return 0;
}
