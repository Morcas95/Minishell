NAME = libft.a

SRC = ft_isalpha.c \
      ft_isdigit.c \
      ft_isalnum.c \
      ft_isascii.c \
      ft_isprint.c \
      ft_strlen.c \
      ft_memset.c \
      ft_bzero.c \
      ft_memcpy.c \
      ft_memmove.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strncmp.c \
      ft_toupper.c \
      ft_tolower.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
      ft_strtrim.c \
      ft_split.c \
      ft_itoa.c \
      ft_strmapi.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_putnbr_fd.c \
      get_next_line.c \
      get_next_line_utils.c \
      ft_putunsigned.c \
      ft_putstr.c \
      ft_putptr.c \
      ft_putnbr.c \
      ft_puthex.c \
      ft_puthex_upper.c \
      ft_putchar.c \
      ft_printf.c \
      const_ft_substr.c \
      const_ft_strjoin.c \
      ft_split_pipex.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_FILES:.c=.o)

CC = cc 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME) $(BONUS_OBJ)
	@ar rcs $(NAME) $(BONUS_OBJ)

clean:
	@rm -f $(OBJ)
	@rm -f $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
