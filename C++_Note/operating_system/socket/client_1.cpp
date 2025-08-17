// This code is a simple TCP client that connects to a server_1 on localhost at
// port 8080 and sends a message.
// It uses the POSIX socket API to create a socket, connect to the server, and
// send data.
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  if (connect(s, (sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    return 1;
  }

  const char *msg = "Here is the message";
  send(s, msg, strlen(msg), 0);

  close(s);
  return 0;
}
