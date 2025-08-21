// compiled with: gcc -o registry registry.c
// This is a simple service registry that listens for service registrations
// and lookups. It maintains a table of services and their ports.
// It listens on port 8888 and supports two commands: "REGISTER <name> <port>"
// and "LOOKUP <name>".
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define REG_PORT 8888
#define BUFSZ 256

struct {
  char name[64];
  int port;
} table[128];

int nsvc = 0;

int main() {
  int srv = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in a = {0};
  a.sin_family = AF_INET;
  a.sin_addr.s_addr = htonl(INADDR_ANY);
  a.sin_port = htons(REG_PORT);
  if (bind(srv, (struct sockaddr *)&a, sizeof(a)) < 0) {
    perror("bind");
    return 1;
  }
  if (listen(srv, 16) < 0) {
    perror("listen");
    return 1;
  }
  printf("registry on %d\n", REG_PORT);

  for (;;) {
    int c = accept(srv, NULL, NULL);
    if (c < 0)
      continue;
    char buf[BUFSZ] = {0};
    ssize_t k = recv(c, buf, sizeof(buf) - 1, 0);

    if (k > 0) {
      char cmd[16], name[64];
      int port;
      if (sscanf(buf, "REGISTER %63s %d", name, &port) == 2) {
        int i;
        for (int i = 0; i < nsvc; ++i) {
          if (!strcmp(table[i].name, name)) {
            table[i].port = port;
            break;
          }
        }
        if (i == nsvc && nsvc < 128) {
          strcpy(table[nsvc].name, name);
          table[nsvc++].port = port;
        }
        dprintf(c, "OK\n");
      } else if (sscanf(buf, "LOOKUP %63s", name) == 1) {
        int i, found = -1;
        for (i = 0; i < nsvc; i++)
          if (!strcmp(table[i].name, name)) {
            found = i;
            break;
          }
        if (found >= 0)
          dprintf(c, "PORT %d\n", table[found].port);
        else
          dprintf(c, "NOTFOUND\n");
      } else
        dprintf(c, "ERROR\n");
    }
    close(c);
  }
}
