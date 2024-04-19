#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void execute_cmd(char *cmd, char **env) {
  char *path;
  char **args;

  args = ft_split(cmd, ' ');
  if (!args)
    pipex_error("split",1);
  path = get_cmd_path(args[0], env);
  execve(path, args, env);
}

int execute_first_cmd(t_pipex *pipex) 
{
	int ifd;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		perror("fork");
	if(pid != 0)
		return pid;
	ifd = open(pipex->av[1],O_RDONLY);
	if(ifd == -1)
		pipex_error(pipex->av[1],EXIT_FAILURE);
	dup2(ifd,STDIN_FILENO);
	dup2(pipex->pipe_fd[WRITE],STDOUT_FILENO);
	close(ifd);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[2],pipex->env);
	return -1;
}

int execute_last_cmd(t_pipex *pipex) 
{
	int ofd;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		pipex_error("fork",1);
	if(pid != 0)
		return pid;
	ofd = open(pipex->av[4],O_RDWR|O_CREAT,0664);
	if(ofd == -1)
		pipex_error("can't create file",1);
	dup2(ofd,STDOUT_FILENO);
	dup2(pipex->pipe_fd[READ],STDIN_FILENO);
	close(ofd);
	close(pipex->pipe_fd[READ]);
	execute_cmd(pipex->av[3],pipex->env);
	return -1;
}

int main(int ac, char **av, char **env) // ./pipex file1 cmd1 cmd2 file2
{
	int status1;
	int status2;
	t_pipex pipex;
	if(ac == 5)
	{
		pipex.av = av;
		pipex.env = env;
		if(pipe(pipex.pipe_fd) == -1)
			perror("pipe");
		int pid_1 = execute_first_cmd(&pipex);
		close(pipex.pipe_fd[WRITE]);
		int pid_2 = execute_last_cmd(&pipex);
		close(pipex.pipe_fd[READ]);
		int p2 = 0;
		while(waitpid(p2,&status2,0) != -1)
		{
		 p2 = WEXITSTATUS(status2);
			if(p2 == 127 || p2 == 126 || p2 == -1 || p2 == 0)
			{
				exit(p2);
			}
		
		}
		return p2;
	}
return (0);
}
