#include "libft/libft.h"
#include "pipex.h"
#include <unistd.h>

void pipex_error(char *str,int e) {
	if(e == 127)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(str, 2);
		if(ft_strchr(str, '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else 
			ft_putstr_fd(": command not found \n", 2);
	}
	else
	{
		ft_putstr_fd("pipex: ", 2);
		perror(str);
	}
	exit(e);
}
