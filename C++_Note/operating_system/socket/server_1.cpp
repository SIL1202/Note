// This code is a simple TCP server that listens for incoming connections on
// port 8080. It uses the POSIX socket API to create a socket, bind it to an
// address, listen for connections, accept a client connection, and receive data
// from the client. The server can handle a single client connection at a time
// and prints the received data to the standard output.
#include <arpa/inet.h>
#include <cstdio> // perror, puts, printf
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // These code is a simple way to implement socket communication. The following
  // details is below:
  // 1. Create a socket using socket(AF_INET, SOCK_STREAM, 0).
  // 2. Set socket options using setsockopt() to allow reuse of the address.
  // 3. Bind the socket to an address using bind().
  // 4. Listen for incoming connections using listen().
  // 5. Accept a connection using accept().
  // 6. Receive data from the client using recv().
  int s = socket(AF_INET, SOCK_STREAM, 0);
  int yes = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = htonl(INADDR_ANY); // address: 0.0.0.0:

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    return EXIT_FAILURE;
  }

  listen(s, 5);

  puts("server listening on 0.0.0.0:8080");

  sockaddr_in cli{};
  socklen_t len = sizeof(cli);
  int c = accept(s, (struct sockaddr *)&cli, &len); // listen_fd = s
  // listen_fd 必須是已經呼叫過 listen() 的 TCP socket，否則會報錯 EINVAL。
  //
  // 當 client 呼叫 connect()，TCP 協定會跟 server 的 kernel 完成
  // 三向交握 (3-way handshake)。
  //
  // 成功握手後，這個連線會被放進「已完成佇列」(completed connection queue)。
  // accept() 會從這個佇列裡拿出一個連線。
  //
  // cli 結構會被填上對方的 IP 和 port。
  // len 會被更新為實際大小。
  //
  // 回傳值 c 就是新的 socket file descriptor
  // 可以對 c 用 recv()、send()，和這個 client 交換資料。

  if (c < 0) {
    perror("accept");
    return EXIT_FAILURE;
  }
  puts("client connected");

  char buf[1024];
  ssize_t n = recv(c, buf, sizeof(buf) - 1, 0);
  // ssize_t 是 standard POSIX API 預期的型別
  if (n > 0) {
    buf[n] = '\0';
    printf("recv: %s\n", buf);
  }

  close(c);
  close(s);
  return EXIT_SUCCESS;
}
