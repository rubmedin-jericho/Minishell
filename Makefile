CC = cc
FLAGS = -Wall -Werror -Wextra -lreadline -lncurses
CFLAGS = -Wall -Werror -Wextra #No borrar porque estas flags se compilan con los .o porque si intentas compilar con las flag del readline da error.
NAME = minishell
HEADER = minishell.h
SRCS = minishell_main.c \
	   minishell_parser.c \
	   minishell_utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
