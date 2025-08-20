// This program retrieves and displays information about a file specified by the
// user. It shows the file size, owner UID and GID, owner's name, group's name,
// and the file's permissions in a human-readable format.
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
  // ensure at least a file after argv[0]
  if (argc != 2) {
    printf("usage:\n%s <file path>\n", argv[0]);
    return 1;
  }

  struct stat st; // storing information of the file
  // if file doesn't exist, return -1
  if (stat(argv[1], &st) == -1) {
    perror("stat failed\n");
    return 1;
  }

  printf("file size: %lld bytes\n", st.st_size);
  printf("owner UID: %d\n", st.st_uid);
  printf("owner GID: %d\n", st.st_gid);

  struct passwd *pw = getpwuid(st.st_uid);
  struct group *gr = getgrgid(st.st_gid);
  if (pw)
    printf("owner's name: %s\n", pw->pw_name);
  if (gr)
    printf("group's name: %s\n", gr->gr_name);

  printf("authority: ");
  printf((S_ISDIR(st.st_mode)) ? "d" : "-");
  printf((st.st_mode & S_IRUSR) ? "r" : "-");
  printf((st.st_mode & S_IWUSR) ? "w" : "-");
  printf((st.st_mode & S_IXUSR) ? "x" : "-");
  printf((st.st_mode & S_IRGRP) ? "r" : "-");
  printf((st.st_mode & S_IWGRP) ? "w" : "-");
  printf((st.st_mode & S_IXGRP) ? "x" : "-");
  printf((st.st_mode & S_IROTH) ? "r" : "-");
  printf((st.st_mode & S_IWOTH) ? "w" : "-");
  printf((st.st_mode & S_IXOTH) ? "x" : "-");
  printf("\n");
  return 0;
}
