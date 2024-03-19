#include "pipex.h"

void	execute_cmd(char *cmd, char **env)
{
	char	*path;
	char	**args;

	args = ft_split(cmd, ' ');
	path = ft_whereis(args[0], env);
	execve(path, args, env);
}

void	execute_cmd2(char *cmd, char **env)
{
	execve("/usr/bin/tr", (char *[]){"tr", "a-z", "A-Z", NULL}, env);
}
int	main(int ac, char **av, char **env) // ./pipex file1 cmd1 cmd2 file2
{
	pid_t child_pid;
	int fd[2];
	int ifd;
	int ofd;
	if (ac < 3)
		return (0);
	ifd = open(av[1], O_RDONLY);
	if (ifd == -1)
	{
		perror("");
	}
	ofd = open(av[2], O_WRONLY | O_APPEND | O_CREAT, 0644);
	pipe(fd);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		dup2(ifd, STDIN_FILENO);
		close(ifd);
		execute_cmd("cat", env);
	}
	else
	{
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		dup2(ofd, STDOUT_FILENO);
		execute_cmd("tr a-z A-Z", env);
	}
	return (0);
}