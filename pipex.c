#include "pipex.h"

void pipex_error(char *str) {
  printf("error : %s\n", str);
  exit(0);
}
void execute_cmd(char *cmd, char **env) {
  char *path;
  char **args;

  args = ft_split(cmd, ' ');
  if (!args)
    pipex_error("split");
  path = ft_whereis(args[0], env);
  execve(path, args, env);
}
void execute_first_cmd(char **av, char **env) { int infd; }

int main(int ac, char **av, char **env) // ./pipex file1 cmd1 cmd2 file2
{
  pid_t child_pid;
  pid_t child_pid2;
  int fd[2];
  int ifd;
  int ofd;
  if (ac < 5)
    return (0);
  ifd = open(av[1], O_RDONLY);
  ofd = open(av[4], O_WRONLY | O_CREAT, 0644);
  pipe(fd);
  child_pid = fork1();
  if (child_pid == 0) {
    close(fd[READ]);
    dup2(fd[WRITE], STDOUT_FILENO);
    close(fd[WRITE]);
    dup2(ifd, STDIN_FILENO);
    close(ifd);
    execute_cmd(av[2], env);
  } else {
    close(fd[WRITE]);
    dup2(fd[READ], STDIN_FILENO);
    close(fd[READ]);
    dup2(ofd, STDOUT_FILENO);
    close(ofd);
    execute_cmd(av[3], env);
  }
  return (0);
}
