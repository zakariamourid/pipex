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
		pipex_error(cmd,127);
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
			if(!access(cmd_path, X_OK)) {
				free_all(paths);
				free(paths);
				free(cmd2);
				return cmd_path;
			}
			else
			{	
				pipex_error(cmd_path,126);
			};
		}
		i++;
		free(cmd_path);
	}
	pipex_error(cmd,127);
	exit(127);
	return NULL;
}

char	*get_cmd_path(char *cmd, t_pipex *pipex) 
{
	char *path;

	if(ft_strchr(cmd,'/'))
	{
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return cmd;
			else
			 pipex_error(cmd, 126);;
		}
		pipex_error(cmd,127);
	}
	path = NULL;
	while (*pipex->env)
	{
		if (!ft_strncmp(*pipex->env, "PATH=", 5))
			path = *pipex->env;
		pipex->env++;
	}
	cmd = ft_look_in_path(cmd, path);
	return (cmd);
}

