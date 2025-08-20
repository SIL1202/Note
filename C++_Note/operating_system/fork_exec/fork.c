// This program demonstrates how to use fork()
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  puts("inside fork.c\n");

  int i, pid;
  pid = fork();

  printf("Forking...the pid: %d\n", pid);
  for (i = 0; i < 5; i++)
    printf(" %d    %d\n", i, getpid());

  // parent process must waits for the child process to finish.
  if (pid)
    wait(NULL);
  return 0;
}
