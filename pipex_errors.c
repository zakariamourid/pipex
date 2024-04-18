#include "pipex.h"
void pipex_error(char *str,int e) {
	printf("error : %s\n", str);
	perror(str);
	exit(e);
}
