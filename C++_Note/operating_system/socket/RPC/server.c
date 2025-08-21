// Compile with: gcc -o server server.c
// This is a simple server that provides an "add" service.
// It listens on a random port, registers itself with a registry running on
// localhost at port// 8888, and processes incoming requests to add two numbers.
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REG_PORT 8888
#define BUFSZ 256

long add(long a, long b) { return a + b; }

int main() {
  // (a) 綁 0 由 OS 配一個臨時埠
  int srv = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in a = {0};
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  a.sin_port = htons(0);
  bind(srv, (struct sockaddr *)&a, sizeof(a));
  listen(srv, 16);

  // 取得實際埠號
  socklen_t len = sizeof(a);
  getsockname(srv, (struct sockaddr *)&a, &len);
  int port = ntohs(a.sin_port);
  printf("service 'add' on port %d\n", port);

  // (b) 向 registry 註冊
  int r = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in ra = {0};
  ra.sin_family = AF_INET;
  ra.sin_port = htons(REG_PORT);
  inet_pton(AF_INET, "127.0.0.1", &ra.sin_addr);
  connect(r, (struct sockaddr *)&ra, sizeof(ra));
  dprintf(r, "REGISTER add %d\n", port);
  char tmp[BUFSZ] = {0};
  read(r, tmp, sizeof(tmp));
  close(r);

  // (c) 服務 loop：協定 "ADD a b\n" → 回 "RESULT x\n"
  for (;;) {
    int c = accept(srv, NULL, NULL);
    if (c < 0)
      continue;
    char buf[BUFSZ] = {0};
    ssize_t n = recv(c, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
      long x, y;
      if (sscanf(buf, "ADD %ld %ld", &x, &y) == 2)
        dprintf(c, "RESULT %ld\n", add(x, y));
      else
        dprintf(c, "ERROR\n");
    }
    close(c);
  }
}
