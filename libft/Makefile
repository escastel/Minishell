NAME = libft.a

FILES = ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_bzero.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_tolower.c \
ft_toupper.c \
ft_memcpy.c \
ft_strncmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_memmove.c \
ft_strchr.c \
ft_strrchr.c \
ft_memchr.c \
ft_memcmp.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strjoin.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_strmapi.c \
ft_striteri.c \
ft_strtrim.c \
ft_itoa.c \
ft_split.c \
get_next_line_bonus.c \
get_next_line_utils_bonus.c \
ft_printf.c \
ft_putptr.c \
ft_puthexa.c \
ft_putunsignbr.c \
ft_count_unsignb.c \
ft_putnbr.c \
ft_count_nb.c \
ft_putstr.c \
ft_putchar.c \
ft_abs.c \
ft_lstnew_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstsize_bonus.c \
ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c \
ft_lstclear_bonus.c \
ft_lstiter_bonus.c \
ft_strcmp.c \
ft_strrlen.c \
get_next_line2.c \
get_next_line2_utils.c

OBJECTS = $(FILES:%.c=obj/%.o)

OBJECTS_DIR = obj

FLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME):		$(OBJECTS)
					@ ar rcs $(NAME) $(OBJECTS)

$(OBJECTS): 	obj/%.o : %.c
					@ mkdir -p obj
					@ gcc $(FLAGS) -c $< -o $@
	
clean:
					@ rm -rf $(OBJECTS) $(OBJECTS_DIR)

fclean:
					@ rm -rf $(NAME) $(OBJECTS) $(OBJECTS_DIR)

re: fclean all

.PHONY : all clean fclean re
