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
  char **cmd_args;
} t_pipex;
char *ft_whereis(char *cmd, char **env);
void pipex_error(char *str,int e);
pid_t fork1();
#define WRITE 1
#define READ 0

#endif
