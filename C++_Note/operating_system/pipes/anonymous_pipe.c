#include <stdio.h>    // for printf, perror, puts, size_t
#include <string.h>   // for strlen
#include <sys/wait.h> // for wait()
#include <unistd.h>   // for pipe(), fork(), read(), write(), close(), _wait()
#define BUFFER_SIZE 25
#define READ_END 0  // index for the read end of the pipe
#define WRITE_END 1 // index for the write end of the pipe

int main() {
  // message that the parent will write into the pipe
  char write_msg[BUFFER_SIZE] = "Hello World";
  // buffer for the child to read into, initialized with zeros
  char read_msg[BUFFER_SIZE] = {0};

  int fd[2]; // file descriptors for the pipe: fd[0] is read end, fd[1] is write
             // end
  if (pipe(fd) == -1) {    // create the pipe
    perror("pipe failed"); // print error if pipe creation fails
    return 1;
  }

  pid_t pid = fork(); // create a child process
  if (pid < 0) {      // fork failed
    perror("fork");
    return 1;
  } else if (pid == 0) {  // child process
    close(fd[WRITE_END]); // child doesn’t need the write end → close it

    // read data from the pipe into read_msg
    // read at most sizeof(read_msg)-1 so there’s space for '\0'
    ssize_t n = read(fd[READ_END], read_msg, sizeof(read_msg) - 1);
    if (n < 0) { // check for read error
      perror("read failed");
      _exit(1); // exit immediately if read failed
    }

    // manually add a null terminator at the end (since read doesn’t add it)
    read_msg[n] = '\0';
    printf("read message from the pipe: %s\n", read_msg);

    close(fd[READ_END]); // close the read end after finishing
  } else {               // parent process
    close(fd[READ_END]); // parent doesn’t need the read end → close it

    // calculate the message length including '\0'
    size_t len = strlen(write_msg) + 1;
    // write the message into the pipe, check if full length was written
    if (write(fd[WRITE_END], write_msg, len) != (ssize_t)len) {
      perror("write failed");
    }

    close(fd[WRITE_END]);      // close the write end after writing
    wait(NULL);                // wait for the child process to finish (reap it)
    puts("mission completed"); // final confirmation message
  }

  return 0;
}
