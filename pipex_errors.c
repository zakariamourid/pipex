#include "pipex.h"
void pipex_error(char *str,int e) {
	perror(str);
	exit(e);
}
//char *get_cmd_path(char *cmd,char *path)
//{
//	char **paths;
//	char *cmd_path;
//	char *cmd2;
//	cmd2 = ft_strjoin("/", cmd);
//	paths = ft_split(path + 5, ':');
//	cmd_path = 0;
//	if(!paths)
//		pipex_error("split", 1);
//	while(*paths)
//	{
//		path = ft_strjoin(*paths, cmd2);
//		if(!access(path,X_OK))
//		{
//			return path;
//		}
//		paths++;
//	}
//	return NULL;
//}
