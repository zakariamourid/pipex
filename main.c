#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define WRITE 1
#define READ 0;
void execute_cmd(int *fd,char **env)
{
  int fdt;
  fdt = open("test.txt",O_RDWR);
  dup2(fdt,STDIN_FILENO);
  close(fdt);
  dup2(fd[WRITE],STDOUT_FILENO);
  execve("/usr/bin/tr",(char*[]){"tr","a-z","A-Z",NULL},env);
}

void execute_cmd2(int *fd,char **env)
{
  int fd;
  fd = open("test.txt",O_RDWR);
  dup2(fd,0);
  execve("/bin/cat",(char*[]){"cat",NULL},env);
}
int main(int ac,char **av,char **env)
{
  pid_t child_pid;
  int fd[2];
  pipe(fd);
  child_pid = fork();
  if(child_pid == 0)
  {
    execute_cmd(fd,env);
    printf("im the child my pid is %d\n",getpid());
  }
  else{
    wait(0);
    execute_cmd2(fd,env);
    printf("im the parent my pid is %d\n",getpid());
  }
 return 0;
}