#include <fcntl.h> // open(), O_EVTONLY
#include <stdio.h>
#include <sys/event.h>
#include <unistd.h> // close() 等

int main() {
  // the file name
  const char *filename = "file.txt";

  int fd = open(filename, O_EVTONLY);
  if (fd < 0) {
    perror("file open failed");
    return 1;
  }

  // create new kqueue for register and recieve
  int kq = kqueue();
  if (kq == -1) {
    perror("create kqueue failed");
    return 1;
  }

  // create kevent structure to descript the monitoring event
  struct kevent ev;
  EV_SET(
      &ev, fd, EVFILT_VNODE,         // 針對 vnode（檔案）事件
      EV_ADD | EV_ENABLE | EV_CLEAR, // 加入事件、啟用、每次觸發後自動清除狀態
      NOTE_WRITE | NOTE_DELETE | NOTE_ATTRIB | NOTE_RENAME, // 要監控的事件類型
      0, NULL);

  printf("monitoring %s\n", filename);

  while (1) {
    struct kevent event; // 用來接收觸發後的事件結果

    // 將我們的事件送進 kqueue，並等待事件發生（阻塞直到有事件）
    int nev = kevent(kq, &ev, 1, &event, 1, NULL);
    if (nev == -1) {
      perror("kevent"); // 若 kevent 執行失敗
      break;
    } else if (nev > 0) {
      // 有事件發生，開始比對是什麼類型的事件
      printf("檔案有變化：");

      if (event.fflags & NOTE_WRITE)
        printf("[寫入] "); // 檔案內容被修改

      if (event.fflags & NOTE_ATTRIB)
        printf("[屬性變更] "); // 權限、擁有者或時間被改變

      if (event.fflags & NOTE_DELETE)
        printf("[被刪除] "); // 檔案被刪除

      if (event.fflags & NOTE_RENAME)
        printf("[被重新命名] "); // 檔案被改名

      printf("\n");
    }
  }

  // 關閉檔案與 kqueue
  close(fd);
}
