CC= cc
CFLAGS= -Wall -Wextra #-Werror
NAME= pipex
CFILES = ft_whereis.c pipex.c pipex_errors.c
OFILES = $(CFILES:.c=.o)
LINKS= -lft -L.

all: $(NAME)
$(NAME): $(OFILES)
	cc $(OFILES) -o $(NAME) $(CFLAGS) $(LINKS)
clean:
	rm -rf $(OFILES)
fclean: clean
	rm -rf $(NAME)
re: fclean all
