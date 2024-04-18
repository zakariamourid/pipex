#include "pipex.h"
#include <stdio.h>
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>

void execute_cmd(char *cmd, char **env) {
  char *path;
  char **args;

  args = ft_split(cmd, ' ');
  if (!args)
    pipex_error("split",1);
  path = ft_whereis(args[0], env);
  execve(path, args, env);
}
void execute_first_cmd(t_pipex *pipex) 
{
	int ifd;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		perror("fork");
	if(pid != 0)
		return;
	ifd = open(pipex->av[1],O_RDONLY);
	if(ifd == -1)
	{
		perror("ifd");
		exit(0);
	}
	dup2(ifd,STDIN_FILENO);
	dup2(pipex->pipe_fd[WRITE],STDOUT_FILENO);
	close(ifd);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[2],pipex->env);
}

void execute_last_cmd(t_pipex *pipex) 
{
	int ofd;
	pid_t pid;
	pid = fork();
	if(pid == -1)
		pipex_error("fork",1);
	if(pid != 0)
		return;
	ofd = open(pipex->av[4],O_RDWR|O_CREAT,0664);
	if(ofd == -1)
		pipex_error("can't create file",1);
	dup2(ofd,STDOUT_FILENO);
	dup2(pipex->pipe_fd[READ],STDIN_FILENO);
	close(ofd);
	close(pipex->pipe_fd[READ]);
	execute_cmd(pipex->av[3],pipex->env);
}

int main(int ac, char **av, char **env) // ./pipex file1 cmd1 cmd2 file2
{
	pid_t child_pid;
	pid_t child_pid2;
	t_pipex pipex;
	if(ac == 5)
	{
		pipex.av = av;
		pipex.env = env;
		if(pipe(pipex.pipe_fd) == -1)
			perror("pipe");
		execute_first_cmd(&pipex);
		close(pipex.pipe_fd[WRITE]);
		execute_last_cmd(&pipex);
		close(pipex.pipe_fd[READ]);
	}
return (0);
}
