#include "pipex.h"

void	execute_command(char **env)
{
	int		fd;
	int		fd2;

	char *args[] = {"tr", "a-z", "A-Z", NULL};
	fd = open("test.txt", O_RDONLY);
	fd2 = open("result.txt", O_RDWR | O_CREAT);
	dup2(fd, 0);
	dup2(fd2, 1);
	close(fd);
	close(fd2);
	execve("/usr/bin/tr", args, env);
	perror("problema");
}
int	main(int ac, char **av, char **env)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		execute_command(env);
	}
	else
	{
		wait(NULL);
		printf("main program is finished !!!");
	}
	return (0);
}
