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
	printf("cmd args = %p\n",pipex->cmd_args);
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

int execute_commands(t_pipex *pipex)
{
	int i = 3;
	int pipefd[2];
//	char ***commands = (char ***) malloc(sizeof(char **) * (pipex->ac - 3 - 1));
//	while(i < pipex->ac - 1)
//	{
//		if(pipe(pipefd))
//		{
//			if(fork() == 0)
//			{
//				dup2(pipex->pipe_fd[READ],STDIN_FILENO);
//				close(pipex->pipe_fd[READ]);
//				dup2(pipefd[WRITE],STDOUT_FILENO);
//				close(pipefd[WRITE]);
//				pipex->pipe_fd[READ] = pipefd[READ];
//				close(pipefd[READ]);
//				execute_cmd(pipex->av[i],pipex);
//			}
//		}
//		i++;
//	}
	while(i <= pipex->ac - 1)
	{
		printf("cmd=%s\n",pipex->av[i]);
		i++;
	}
	return 0;
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
	ofd = open(pipex->av[pipex->ac - 1],O_RDWR | O_CREAT,0664);
	if(ofd == -1)
		pipex_error(pipex->av[pipex->ac - 1],1);
	dup2(ofd,STDOUT_FILENO);
	close(ofd);
	dup2(pipex->pipe_fd[READ],STDIN_FILENO);
	close(pipex->pipe_fd[READ]);
	close(pipex->pipe_fd[WRITE]);
	execute_cmd(pipex->av[pipex->ac - 2],pipex);
	return -1;
}
int main(int ac, char **av, char **env) // ./pipex file1 cmd1 cmd2 cmd3 cmd4 file2
{
//	int status1;
//	int status2;
//	status1 = 0;
//	status2 = 0;
	t_pipex *pipex;
	pipex =get_pipex();
//	int p2 = 0;
//	int p1 = 0;
	pipex->av = av;
	pipex->env = env;
	pipex->ac = ac;
	if(pipe(pipex->pipe_fd) == -1)
		perror("pipe");
	execute_commands(pipex);
	return 0;
	//p1=	execute_first_cmd(pipex);
	//close(pipex->pipe_fd[WRITE]);
	//p2 = execute_last_cmd(pipex);
	//close(pipex->pipe_fd[READ]);
	//waitpid(p1,&status1,0);
//	waitpid(p2,&status2,0);
//	if((status2 >> 8))
//		return (status2 >> 8);
//	return (status2 + 128);
}
