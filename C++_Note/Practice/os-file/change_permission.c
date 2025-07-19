#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("用法：%s <檔案路徑> <八進位權限，例如 644>\n", argv[0]);
    return 1;
  }

  const char *filename = argv[1];
  int mode;
  sscanf(argv[2], "%o", &mode); // 轉成八進位整數

  if (chmod(filename, mode) == -1) {
    perror("chmod 失敗");
    return 1;
  }

  printf("成功變更 %s 的權限為 %o\n", filename, mode);
  return 0;
}
