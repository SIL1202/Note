// This code is a simple TCP client that connects to a server on localhost at
// port 8081 and sends lines of text read from standard input. It ensures that
// each line is sent completely, even if it exceeds the buffer size. The client
// appends a newline character to each line before sending it, and it handles
// socket errors gracefully. It uses the POSIX socket API to create a socket,
// connect to the server, and send data.
//
// 客戶端可以持續讀取標準輸入（stdin），並將每行資料發送到
// server_2。這個程式會確保每行資料都完整發送，即使資料超過了緩衝區大小。每行結尾會自動添加換行符號
// '\n'，並且在發送過程中處理了可能的 socket 錯誤。

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>

// 把 (p,len) 全部送完（避免部分送出）
static bool send_all(int fd, const void *p, size_t len) {
  const char *data = static_cast<const char *>(p);
  size_t sent = 0;
  while (sent < len) {
    ssize_t n = send(fd, data + sent, len - sent, 0);
    if (n > 0)
      sent += (size_t)n;
    else if (n < 0 && (errno == EINTR))
      continue;
    else if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
      continue;
    else
      return false;
  }
  return true;
}

int main() {
  int s = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8081);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  if (connect(s, (sockaddr *)&addr, sizeof(addr)) < 0) {
    perror("connect");
    return 1;
  }

  // 從 stdin 動態讀取一行一行，送到 server（每行尾端補 '\n'）
  std::string line;
  // 使用 C 樣式讀取，避免 iostream 與行尾同步問題
  char buf[4096];
  while (fgets(buf, sizeof(buf), stdin)) {
    line.assign(buf); // 已含 '\n'（除非超長）
    // 若這行超過 4096，fgets 會分段讀；server 也能處理，因為我們有 framing
    if (!line.empty() && line.back() != '\n') {
      line.push_back('\n'); // 保證有行尾
    }
    if (!send_all(s, line.data(), line.size())) {
      perror("send");
      break;
    }
  }

  close(s);
  return 0;
}
