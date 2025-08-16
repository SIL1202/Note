#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr); // ★ 連到本機

  connect(s, (sockaddr *)&addr, sizeof(addr));

  const char *msg = "Hello, server!";
  send(s, msg, strlen(msg), 0);

  close(s);
  return 0;
}
