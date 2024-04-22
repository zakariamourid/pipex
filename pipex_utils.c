#include "pipex.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <unistd.h>

void free_all(char **data,char *cmd) 
{
	int i;

	i = 0;
	if(!data)
		return;
	while(data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	free(cmd);
}
char *ft_look_in_path(char *cmd,char *path)
{
	if(!cmd || !path)
		pipex_error(cmd,127);
	char *cmd_path;
	char **paths = ft_split(path + 5,":");
	char *cmd2 = ft_strjoin("/",cmd);
	int i = 0;
	while(paths[i])
	{
	cmd_path = ft_strjoin(paths[i],cmd2);
  	if(!access(cmd_path, F_OK))
		{
			if(!access(cmd_path, X_OK)) {
				free_all(paths,cmd2);
				return cmd_path;
			}
			else
				pipex_error(cmd_path,126);
		}
		i++;
		free(cmd_path);
	}
	pipex_error(cmd,127);
	return NULL;
}

void check_dir(char *cmd)
{
	int fd;
	fd = open(cmd,O_DIRECTORY);
	if(fd != -1)
		pipex_error(cmd, 1026);
	close(fd);
}

char	*get_cmd_path(char *cmd, t_pipex *pipex) 
{
	char *path;

	path = NULL;
	while (*pipex->env)
	{
		if (!ft_strncmp(*pipex->env, "PATH=", 5))
			path = *pipex->env;
		pipex->env++;
	}
	if(!cmd || !*cmd)
		exit(0);
	if(ft_strchr(cmd,'/') || !path)
	{
		if (!access(cmd, F_OK))
		{
			check_dir(cmd);
			if (!access(cmd, X_OK))
				return cmd;
			else
			 pipex_error(cmd, 126);
		}
		pipex_error(cmd,127);
	}
	return (ft_look_in_path(cmd,path));
}

