#include "pipex.h"
#include "libft/libft.h"
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
	data = NULL;
}
char *ft_look_in_path(char *cmd,char *path)
{
	if(!cmd || !path)
		return NULL;
	cmd = ft_strjoin("/",cmd);
	char *cmd_path;
	path+=5;
	char **paths = ft_split(path,':');
	int i =0;
	while(paths[i])
	{
		cmd_path = ft_strjoin(paths[i],cmd);
		if(!access(cmd_path, F_OK))
		{
			printf("it exists in path bro \n");
			if(!access(cmd_path, X_OK))
				return cmd_path;
			else
			{	
				pipex_error(cmd,126);
				return (free(cmd),free_all(paths),NULL);
			};
		}
		free(cmd_path);
		i++;
	}
	free(cmd);
	free_all(paths);
	return NULL;
}
char	*get_cmd_path(char *cmd, char **env)
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
		if (!access(cmd_path, F_OK))
		{
			if (!access(cmd_path, X_OK))
				return cmd_path;
			else
			 pipex_error(cmd, 126);;
		}
		pipex_error(cmd, 127);;
	}
	cmd = ft_look_in_path(cmd, path);
	if(!cmd)
		pipex_error("command not found",127);
	return (cmd);
}
int main(int ac,char **av,char **env)
{
	if(ac >= 2)
	{
	char *cmd = av[1];
	char *cmd_path = get_cmd_path(cmd, env);
	printf("cmd path is == %s \n",cmd_path);
	}
}
