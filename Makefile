NAME = pipex

SRC = src/pipex.c src/pipex_utils.c src/pipex_utils1.c

CC = cc
CCFLAGS = -Werror -Wall -Wextra  # -fsanitize=address

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SRC) Includes/pipex.h Makefile
	$(CC) $(CCFLAGS) -IIncludes $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C libft/

clean:
	@make -C libft/

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: re fclean clean all 