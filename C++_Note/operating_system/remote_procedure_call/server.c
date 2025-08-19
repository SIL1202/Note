#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 9000
#define BUFSZ 1024

long func(const long a, const long b) { return a * b; }

int main() {
  int srv = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr = {0};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(PORT);
  if (bind(srv, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }
  if (listen(srv, 8) < 0) {
    perror("listen");
    exit(1);
  }

  printf("RPC server listening on port %d\n", PORT);
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
