#include "pipex.h"
#include "libft/libft.h"
#include <sys/_types/_pid_t.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


t_pipex *get_pipex(void)
{
	static t_pipex pipex;
	return &pipex;
}
void execute_cmd(char *cmd, t_pipex *pipex) {
  char *path;

  pipex->cmd_args = ft_split(cmd, ' ');
  if (!pipex->cmd_args)
    pipex_error("split",1);
  path = get_cmd_path(pipex->cmd_args[0], pipex);
  execve(path, pipex->cmd_args, pipex->env);
	pipex_error("execve", 1);
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
		pipex_error(pipex->av[1],1);
	close(pipex->pipe_fd[READ]);
	dup2(ifd,STDIN_FILENO);
	dup2(pipex->pipe_fd[WRITE],STDOUT_FILENO);
	close(ifd);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[2],pipex);
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
	ofd = open(pipex->av[4],O_RDWR,0664);
	if(ofd == -1)
		pipex_error("can't create file",1);
	dup2(ofd,STDOUT_FILENO);
	close(ofd);
	dup2(pipex->pipe_fd[READ],STDIN_FILENO);
	close(pipex->pipe_fd[READ]);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[3],pipex);
	return -1;
}
int main(int ac, char **av, char **env) // ./pipex file1 cmd1 cmd2 file2
{
	int status1;
	int status2;
	status1 = 0;
	status2 = 0;
	t_pipex *pipex;
	pipex =get_pipex();
	int p2 = 0;
	int p1 = 0;
	if(ac == 5)
	{
		pipex->av = av;
		pipex->env = env;
		if(pipe(pipex->pipe_fd) == -1)
			perror("pipe");
		p1=	execute_first_cmd(pipex);
		close(pipex->pipe_fd[WRITE]);
		p2 = execute_last_cmd(pipex);
		close(pipex->pipe_fd[READ]);
		waitpid(p1,&status1,0);
		waitpid(p2,&status2,0);
	}
	if(WIFEXITED(status2))
		return (status2 >> 8);
	return (status2 + 128);
}
