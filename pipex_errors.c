#include "pipex.h"

void pipex_error(char *str,int e) {
	perror(str);
	exit(e);
}
