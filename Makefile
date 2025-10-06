CC = cc
READLINE = -lreadline -lncurses
CFLAGS = -Wall -Werror -Wextra ## -fsanitize=address -fsanitize=leak ## para analisis de leaks #No borrar porque estas flags se compilan con los .o porque si intentas compilar con las flag del readline da error.
NAME = minishell
LIBFT_DIR = Libft
HEADER = minishell.h $(LIBFT_DIR)/libft.h

SRCS = minishell_main.c \
	   minishell_parser.c \
	   minishell_lexer.c
	   
LIBFT_SRCS = $(LIBFT_DIR)/ft_isalpha.c $(LIBFT_DIR)/ft_isdigit.c \
	$(LIBFT_DIR)/ft_isalnum.c $(LIBFT_DIR)/ft_strlen.c $(LIBFT_DIR)/ft_isascii.c \
	$(LIBFT_DIR)/ft_isprint.c $(LIBFT_DIR)/ft_memset.c $(LIBFT_DIR)/ft_bzero.c \
	$(LIBFT_DIR)/ft_memcpy.c $(LIBFT_DIR)/ft_memmove.c $(LIBFT_DIR)/ft_strlcpy.c \
	$(LIBFT_DIR)/ft_strlcat.c $(LIBFT_DIR)/ft_toupper.c $(LIBFT_DIR)/ft_tolower.c \
	$(LIBFT_DIR)/ft_strchr.c $(LIBFT_DIR)/ft_strrchr.c $(LIBFT_DIR)/ft_strncmp.c \
	$(LIBFT_DIR)/ft_memchr.c $(LIBFT_DIR)/ft_memcmp.c $(LIBFT_DIR)/ft_strnstr.c \
	$(LIBFT_DIR)/ft_atoi.c $(LIBFT_DIR)/ft_calloc.c $(LIBFT_DIR)/ft_strdup.c \
	$(LIBFT_DIR)/ft_substr.c $(LIBFT_DIR)/ft_strtrim.c $(LIBFT_DIR)/ft_split_pipex.c \
	$(LIBFT_DIR)/ft_putnbr_fd.c $(LIBFT_DIR)/ft_itoa.c $(LIBFT_DIR)/ft_strmapi.c \
	$(LIBFT_DIR)/ft_striteri.c $(LIBFT_DIR)/ft_putchar_fd.c $(LIBFT_DIR)/ft_putstr_fd.c \
	$(LIBFT_DIR)/ft_putendl_fd.c $(LIBFT_DIR)/ft_strjoin.c $(LIBFT_DIR)/ft_strcmp.c \
	

OBJS = $(SRCS:.c=.o)

LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJS) Makefile $(HEADRS) ## Si cambia el Makefile o los headers, volver a compilar 
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_OBJS) -o $(NAME) $(READLINE)

%.o: %.c Makefile $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(LIBFT_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
