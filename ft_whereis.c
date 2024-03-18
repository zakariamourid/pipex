#include "pipex.h"

char	*ft_whereis(char *cmd, char **env)
{
	char *path;
	char **paths;
	char *cmd_path;

	cmd_path = cmd;
	if (!access(cmd_path, F_OK))
		return (cmd_path);
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			path = *env;
		**env++;
	}
	paths = ft_split(path + 5, ':');
	while (*paths)
	{
		cmd_path = ft_strjoin(*paths, ft_strjoin("/", cmd));
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
				return (cmd_path);
		}
		free(cmd_path);
		**paths++;
	}
	return (NULL);
}