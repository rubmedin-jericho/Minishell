# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -fsanitize=leak
READLINE = -lreadline -lncurses

# Program name
NAME = minishell

# Directories
SRCS_DIR = src
OBJS_DIR = objs
INCLUDES_DIR = include

# Includes
INCLUDES_FLAG = -I$(INCLUDES_DIR) -Ilibft

# Libft
LIBFT = libft/libft.a
LIBS = -Llibft -lft $(READLINE)

# ---------------------------------------------------------
#                 SOURCE FILE DETECTION
# ---------------------------------------------------------

# Main only in src/
MAIN = $(SRCS_DIR)/main.c

# Parser sources
PARSER_SRCS = \
	$(SRCS_DIR)/parser/parser.c
# Lexer sources
LEXER_SRCS = \
	$(SRCS_DIR)/lexer/lexer.c \
	$(SRCS_DIR)/lexer/list.c \
	$(SRCS_DIR)/lexer/simple_quot.c \
	$(SRCS_DIR)/lexer/utils.c

# Combine all sources
SRCS = $(MAIN) $(PARSER_SRCS) $(LEXER_SRCS)

# Object files
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)


# Colors
GREEN  = \033[0;32m
YELLOW = \033[0;33m
RED    = \033[0;31m
RESET  = \033[0m


# ---------------------------------------------------------
#                   COMPILATION RULES
# ---------------------------------------------------------

all: $(OBJS_DIR) $(LIBFT) $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/lexer

$(NAME): $(OBJS)
	@echo "$(GREEN) - Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(YELLOW) - Compilation finished!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES_FLAG) -c $< -o $@


# ---------------------------------------------------------
#                        LIBFT
# ---------------------------------------------------------
$(LIBFT):
	@make -C libft

# ---------------------------------------------------------
#                      CLEAN RULES
# ---------------------------------------------------------
clean:
	@rm -rf $(OBJS_DIR)
	@make -C libft clean
	@echo "$(RED) - Objects cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "$(RED) - Full clean done$(RESET)"

re: fclean all

nvim: fclean

.PHONY: all clean fclean re nvim
