NAME = minishell

MINISHELL = minishell.a

FILES = minishell.c \
minishell_print.c \
init_structs.c \
env_initialize.c \
lexer.c \
expander.c \
parser.c \
clean_cmd.c \
expander_utils.c \
signal.c \
clean_program.c \
lexer_utils.c \
heredoc.c \
executer.c \
tokens.c

FILES_BUILT = built-ins/builtins_control.c \
built-ins/cd.c \
built-ins/echo.c \
built-ins/env.c \
built-ins/exit.c \
built-ins/export.c \
built-ins/pwd.c \
built-ins/unset.c

OBJECTS = $(FILES:%.c=obj/%.o)

OBJECTS_BUILT = $(FILES_BUILT:built-ins/%.c=built-ins/obj/%.o)

OBJECTS_DIR = obj

OBJECTS_DIR_BUILT = built-ins/obj

FLAGS = -Werror -Wall -Wextra

LIBFT = ./libft/libft.a

LIBFT_PATH = ./libft 

INCLUDE = -I ./include -I /Users/$(USER)/.brew/opt/readline/include

READLINE = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

all: 				$(LIBFT) $(NAME)

$(LIBFT):
						@ make -s -C $(LIBFT_PATH)

$(NAME):			$(OBJECTS) $(OBJECTS_BUILT)
						@ ar rcs $(MINISHELL) $(OBJECTS) $(OBJECTS_BUILT)
						@ gcc $(FLAGS) $(LIBFT) $(INCLUDE) $(READLINE) $(MINISHELL) -o $(NAME)

$(OBJECTS):			obj/%.o : %.c
						@ mkdir -p obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_BUILT):	built-ins/obj/%.o : built-ins/%.c
						@ mkdir -p built-ins/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
						@ rm -rf $(OBJECTS) $(OBJECTS_BUILT) $(OBJECTS_DIR)
						@ make clean -s -C $(LIBFT_PATH)

fclean:
						@ rm -rf $(NAME) $(OBJECTS) $(OBJECTS_BUILT) $(MINISHELL) $(LIBFT) $(OBJECTS_DIR) $(OBJECTS_DIR_BUILT)
						@ make fclean -s -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re