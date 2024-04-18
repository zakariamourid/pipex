CC= cc
CFLAGS= -Wall -Wextra #-Werror
NAME= pipex
CFILES = ft_whereis.c pipex.c pipex_errors.c
OFILES = $(CFILES:.c=.o)
LINKS= -lft -L./libft

all: $(NAME)

$(NAME): $(OFILES)
	@make -C ./libft
	$(CC) $(CFLAGS) $(LINKS) $(OFILES) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.SECONDARY: $(OFILES)
