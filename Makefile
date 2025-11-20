CC = cc
READLINE = -lreadline -lncurses -fsanitize=address -fsanitize=leak
CFLAGS = -Wall -Werror -Wextra## -fsanitize=address -fsanitize=leak ## para analisis de leaks #No borrar porque estas flags se compilan con los .o porque si intentas compilar con las flag del readline da error.
NAME = minishell


B_DIR = builtins

# Includes
INCLUDES_DIR 	= include
INCLUDES_FLAG 	= -I$(INCLUDES_DIR)
INCLUDES		= $(wildcard $(INCLUDES_DIR)/minishell.h)

HEADER = minishell.h

# Objects
OBJS_DIR		= objs/
OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

# Libraries
LIBFT = libft/libft.a
LIBS = -Llibft -lft

SRCS_DIR = src/

SRCS = minishell_main.c \
	   minishell_parser.c \
	   minishell_lexer.c \
	   minishell_list.c \
	   minishell_utils.c \
	   $(B_DIR)/ft_echo.c \
	   $(B_DIR)/ft_pwd.c \
	   $(B_DIR)/ft_env.c \
	   $(B_DIR)/ft_exit.c \
	   $(B_DIR)/builtin_utils.c \
	   minishell_simple_quot.c

# Objects
OBJS_DIR		= objs/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR) :
	@$(MKDIR) $(OBJS_DIR)

$(NAME) : $(OBJS) Makefile $(LIBFT)
	@echo $(GREEN) " - Compiling $(NAME)..." $(RESET)
	@$(CC) $(CFLAGS) $(OBJS) $(LINKER) -o $(NAME) $(LIBS)
	@echo $(YELLOW) " - Compiling FINISHED" $(RESET)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(INCLUDES)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@	

# Library Rules
$(LIBFT):
	@make -C libft

clean :
	@$(RM) $(OBJS_DIR)
	@make clean -C libft
	@echo $(RED) " - Cleaned!" $(RESET)

fclean : clean
	@$(RM) $(NAME) $(LIBFT)
	@echo $(RED) " - Full Cleaned!" $(RESET)

nvim: clean fclean

re: fclean all

.PHONY: all clean fclean re nvim
