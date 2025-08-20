// This program checks if a file exists and prints its access permissions and
// owner name
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s <file path>\n", argv[0]);
    return 1;
  }

  const char *file = argv[1];
  if (access(file, F_OK) == 0) {
    printf("file exist.\n");
    printf("current file's status:\n");
    if (access(file, R_OK) == 0)
      printf("readable\n");
    else
      printf("not readable\n");
    if (access(file, W_OK) == 0)
      printf("writable\n");
    else
      printf("not writable\n");
    if (access(file, X_OK) == 0)
      printf("excutable\n");
    else
      printf("not excutable\n");
  } else
    printf("file doesn't exist.\n");

  struct stat st;
  // check if file exist
  if (stat(file, &st) == -1) {
    perror("stat failed\n");
    return 1;
  }
  // print the owner name in characters
  struct passwd *pw = getpwuid(st.st_uid);
  printf("owner: %s\n", pw->pw_name);

  return 0;
}
