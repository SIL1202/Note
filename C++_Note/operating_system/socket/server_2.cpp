// This is a simple TCP server that listens on port 8081.
// It accepts a client connection and receives data from the client,
// printing each complete line received. The server handles partial lines
// and ensures that any remaining data is printed when the client disconnects.
#include <arpa/inet.h>
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstring>
#include <string>

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);

  int yes = 1;
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8081);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(s, (sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("bind");
    return EXIT_FAILURE;
  }

  listen(s, 8);
  puts("server listening on 0.0.0.0:8081");

  sockaddr_in cli{};
  socklen_t len = sizeof(cli);
  int c = accept(s, (sockaddr *)&cli, &len);
  if (c < 0) {
    perror("accept");
    return 1;
  }
  puts("client connected");

  std::string accum; // 累積還沒切成行的資料
  char buf[4096];
  for (;;) {
    ssize_t n = recv(c, buf, sizeof(buf), 0);
    if (n > 0) {
      accum.append(buf, buf + n);
      // 把累積資料中所有完整的一行(以 '\n' 結尾)取出並輸出
      for (;;) {
        auto pos = accum.find('\n');
        if (pos == std::string::npos)
          break;
        std::string line = accum.substr(0, pos); // 不含 '\n'
        accum.erase(0, pos + 1);
        printf("recv: %s\n", line.c_str());
        fflush(stdout);
      }
    } else if (n == 0) {
      // 對方關閉連線；如果還有殘留資料，最後也印出
      if (!accum.empty()) {
        printf("recv: %s\n", accum.c_str());
      }
      puts("client disconnected");
      break;
    } else {
      perror("recv");
      break;
    }
  }

  close(c);
  close(s);
  return 0;
}
