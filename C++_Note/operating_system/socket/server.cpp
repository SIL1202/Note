#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);
  int yes = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(s, (struct sockaddr *)&addr, sizeof(addr));

  listen(s, 5);

  puts("server listening on 0.0.0.0:8080");

  sockaddr_in cli{};
  socklen_t len = sizeof(cli);
  int c = accept(s, (struct sockaddr *)&cli, &len);
  if (c < 0) {
    perror("accept");
    return 1;
  }
  puts("client connected");

  char buf[1024];
  ssize_t n = recv(c, buf, sizeof(buf) - 1, 0);
  if (n > 0) {
    buf[n] = '\0';
    printf("recv: %s\n", buf);
  }

  close(c);
  close(s);
  return 0;
}
