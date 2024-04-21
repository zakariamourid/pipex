CC= cc
CFLAGS= -Wall -Wextra -fsanitize=address -Werror
NAME= pipex
CFILES =  pipex.c pipex_errors.c pipex_utils.c 
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

.PHONY: all bonus clean fclean re

.SECONDARY: $(OFILES)
