#ifndef PIPEX_H
#define PIPEX_H
#include "./libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
char *ft_whereis(char *cmd, char **env);
pid_t fork1();
#define WRITE 1
#define READ 0

#endif
