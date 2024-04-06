#include "pipex.h"

pid_t fork1() {
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    printf("erorr");
    exit(0);
  }
  return pid;
}
