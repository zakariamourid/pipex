CC= cc
CFLAGS= -Wall -Wextra #-Werror
NAME= pipex
CFILES = ft_whereis.c pipex.c pipex_utils.c
OFILES = $(CFILES:.c=.o)
LINKS= -lft -L./libft
$(NAME):$(OFILES)
	$(CC) $(OFILES) -o $(NAME) $(LINKS) -g
$(OFILES):$(CFILES)
	$(CC) $(CFLAGS) -c $(CFILES) 
all: $(NAME)
clean:
	rm -rf $(OFILES)
fclean: clean
	rm -rf $(NAME)
