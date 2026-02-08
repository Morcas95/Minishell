CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
LIBFT = ./libft/libft.a
INCLUDE = -I./includes
SRC =	./src/main.c \
		./src/signals/signals.c \
		./src/lexer/lexer.c \
		./src/lexer/lexer_utils.c \
		./src/lexer/lexer_words.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

BLACK   := \033[30m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE 	:= \033[96m
MAGENTA := \033[38;5;206m
CYAN    := \033[36m
WHITE   := \033[37m
RESET   := \033[0m
BOLD    := \033[1m
DIM     := \033[2m
ITALIC  := \033[3m
UNDER   := \033[4m
BLINK   := \033[5m
REVERSE := \033[7m
HIDDEN  := \033[8m
PINK 	:= \033[35m

VPATH = ./src:./src/signals:./src/lexer

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) 
	@echo "Compiled with $(GREEN)$(BOLD)$(CFLAGS) -lreadline$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "$(PINK)$(BOLD)----------------------------------------"
	@echo "     $(NAME) = NOW READY FOR USE!"
	@echo "----------------------------------------$(RESET)"

$(LIBFT):
	@$(MAKE) -C ./libft


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "Compiled ✅ $(PINK) $(BOLD) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@echo "$(BLUE) $(BOLD)$(NAME) $(RESET) Cleansed ✅"

re: fclean all

.PHONY: all clean fclean re