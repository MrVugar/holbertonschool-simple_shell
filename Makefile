CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
SRC = shell.c helpers.c
OBJ = $(SRC:.c=.o)
NAME = simple_shell

all: $(NAME)

$(NAME): $(OBJ)
\t$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
\trm -f $(OBJ)

fclean: clean
\trm -f $(NAME)

re: fclean all
