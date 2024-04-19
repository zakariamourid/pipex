#include "pipex.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <sys/unistd.h>
#include <unistd.h>

void free_all(char **data)
{
	if(!data)
		return;
	while(*data)
	{
		free(*data);
		data++;
	}
}
char *ft_look_in_path(char *cmd,char *path)
{
	if(!cmd || !path)
	{
		dprintf(2,"pipex: command not found: %s\n",cmd);
		exit(127);
	}
	char *cmd_path;
	path += 5;
	char **paths = ft_split(path,':');
	char *cmd2 = ft_strjoin("/",cmd);
	int i = 0;
	while(paths[i])
	{
	cmd_path = ft_strjoin(paths[i],cmd2);
  	if(!access(cmd_path, F_OK))
		{
			if(!access(cmd_path, X_OK))
			{
				free_all(paths);
				free(paths);
				free(cmd2);
				return cmd_path;
			}
			else
			{	
				pipex_error(cmd,126);
				return (free(cmd),free_all(paths),NULL);
			};
		}
		i++;
		free(cmd_path);
	}
	free_all(paths);
	free(paths);
	free(cmd2);
	dprintf(2,"pipex: command not found: %s\n",cmd);
	exit(127);
	return NULL;
}

char	*get_cmd_path(char *cmd, char **env)
{
	char *path;
	char *cmd_path;


	if(ft_strchr(cmd_path,'/'))
	{
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
				return cmd_path;
			else
			 pipex_error(cmd, 126);;
		}
		dprintf(2,"pipex: command not found: %s\n",cmd);
		exit(127);
	}
	path = NULL;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			path = *env;
		env++;
	}
	cmd_path = cmd;
	cmd = ft_look_in_path(cmd, path);
	return (cmd);
}

