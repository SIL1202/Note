// This program changes the file permissions of a specified file to a given
// octal value. It takes two command line arguments: the file path and the octal
// permission value. It uses the `chmod` system call to change the file
// permissions and prints a success message if the operation is successful, or
// an error message if it fails.
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
