#include "libft/libft.h"
#include "pipex.h"
#include <sys/unistd.h>

char *get_cmd_path(char *cmd,char *path)
{
	char **paths;
	char *cmd_path;
	char *cmd2;
	cmd2 = ft_strjoin("/", cmd);
	paths = ft_split(path + 5, ':');
	cmd_path = 0;
	if(!paths)
		pipex_error("split", 1);
	while(*paths)
	{
		path = ft_strjoin(*paths, cmd2);
		if(!access(path,X_OK))
		{
			return path;
		}
		paths++;
	}
	return NULL;
}
char	*get_path(char *cmd, char **env)
{
	char *path;
	char *cmd_path;

	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			path = *env;
		env++;
	}
	cmd_path = cmd;
	if(ft_strchr(cmd_path,'/'))
	{
	if (!access(cmd_path, X_OK))
		return (cmd_path);
	}
	return (NULL);
}
