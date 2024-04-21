#ifndef PIPEX_H
#define PIPEX_H
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct s_pipex {
  char **env;
  char **av;
  int in_fd;
  int out_fd;
  int pipe_fd[2];
  int *pids;
  char **cmd_args;
  char *cmd_path;
} t_pipex;
char *ft_whereis(char *cmd, char **env);
void pipex_error(char *str,int e);
pid_t fork1();
char	*get_cmd_path(char *cmd, t_pipex *pipex);
#define WRITE 1
#define READ 0

#endif
