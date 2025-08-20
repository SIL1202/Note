// This program demonstrates how to call execv() and return control after
// finished its process.
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // program below is trying to do execv() and return after the process is
  // finished.
  pid_t pid = fork(); // first step is to fork the process
  if (pid == 0) {     // and call the function in the child process
    execv("./fork", argv);
    perror("execv failed\n"); // only if failed
    _exit(127);
  } else { // parent process
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
      printf("child exit code: %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status))
      printf("child killed by signal: %d\n", WTERMSIG(status));
  }

  puts("");
  puts("return to the main process.");
  return 0;
}
