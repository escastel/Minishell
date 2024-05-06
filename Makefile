NAME = minishell

MINISHELL = minishell.a

FILES = minishell.c 

FILES_BUILT = built-ins/builtins_control.c \
built-ins/cd.c \
built-ins/echo.c \
built-ins/env.c \
built-ins/exit.c \
built-ins/export.c \
built-ins/pwd.c \
built-ins/unset.c \
built-ins/export_utils.c \
built-ins/utils.c

FILES_CLEAN = clean/clean_cmd.c \
clean/clean_program.c

FILES_EXECUTER = executer/executer.c \
executer/executer_utils.c \
executer/executer_process.c

FILES_EXPANDER = expander/expander.c \
expander/expander_utils.c

FILES_INIT = init/init_structs.c \
init/env_initialize.c

FILES_LEXER = lexer/lexer.c \
lexer/lexer_utils.c \
lexer/tokens.c

FILES_PARSER = parser/parser.c \
parser/heredoc.c \
parser/parser_redir.c \
parser/cmd_create.c

FILES_PRINT = print/minishell_print.c

FILES_SIGNAL = signal/signal.c

OBJECTS = $(FILES:%.c=obj/%.o)

OBJECTS_BUILT = $(FILES_BUILT:built-ins/%.c=built-ins/obj/%.o)

OBJECTS_CLEAN = $(FILES_CLEAN:clean/%.c=clean/obj/%.o)

OBJECTS_EXECUTER = $(FILES_EXECUTER:executer/%.c=executer/obj/%.o)

OBJECTS_EXPANDER = $(FILES_EXPANDER:expander/%.c=expander/obj/%.o)

OBJECTS_INIT = $(FILES_INIT:init/%.c=init/obj/%.o)

OBJECTS_LEXER= $(FILES_LEXER:lexer/%.c=lexer/obj/%.o)

OBJECTS_PARSER = $(FILES_PARSER:parser/%.c=parser/obj/%.o)

OBJECTS_PRINT = $(FILES_PRINT:print/%.c=print/obj/%.o)

OBJECTS_SIGNAL = $(FILES_SIGNAL:signal/%.c=signal/obj/%.o)

OBJECTS_DIR = obj

OBJECTS_DIR_BUILT = built-ins/obj

OBJECTS_DIR_CLEAN = clean/obj

OBJECTS_DIR_EXECUTER = executer/obj

OBJECTS_DIR_EXPANDER = expander/obj

OBJECTS_DIR_INIT = init/obj

OBJECTS_DIR_LEXER= lexer/obj

OBJECTS_DIR_PARSER = parser/obj

OBJECTS_DIR_PRINT = print/obj

OBJECTS_DIR_SIGNAL = signal/obj

FLAGS = -Werror -Wall -Wextra

LIBFT = ./libft/libft.a

LIBFT_PATH = ./libft 

INCLUDE = -I ./include -I /Users/$(USER)/.brew/opt/readline/include

READLINE = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline

all: 					$(LIBFT) $(NAME)

$(LIBFT):
							@ make -s -C $(LIBFT_PATH)

$(NAME):				$(OBJECTS) $(OBJECTS_BUILT) $(OBJECTS_CLEAN) $(OBJECTS_EXECUTER) $(OBJECTS_EXPANDER) $(OBJECTS_INIT) $(OBJECTS_LEXER) $(OBJECTS_PARSER) $(OBJECTS_PRINT) $(OBJECTS_SIGNAL)
							@ ar rcs $(MINISHELL) $(OBJECTS) $(OBJECTS_BUILT) $(OBJECTS_CLEAN) $(OBJECTS_EXECUTER) $(OBJECTS_EXPANDER) $(OBJECTS_INIT) $(OBJECTS_LEXER) $(OBJECTS_PARSER) $(OBJECTS_PRINT) $(OBJECTS_SIGNAL)
							@ gcc $(FLAGS) $(LIBFT) $(INCLUDE) $(READLINE) $(MINISHELL) -o $(NAME)

$(OBJECTS):				obj/%.o : %.c
						@ mkdir -p obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_BUILT):		built-ins/obj/%.o : built-ins/%.c
						@ mkdir -p built-ins/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_CLEAN):		clean/obj/%.o : clean/%.c
						@ mkdir -p clean/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@
		
$(OBJECTS_EXECUTER):	executer/obj/%.o : executer/%.c
						@ mkdir -p executer/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_EXPANDER):	expander/obj/%.o : expander/%.c
						@ mkdir -p expander/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_INIT):		init/obj/%.o : init/%.c
						@ mkdir -p init/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_LEXER):		lexer/obj/%.o : lexer/%.c
						@ mkdir -p lexer/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_PARSER):		parser/obj/%.o : parser/%.c
						@ mkdir -p parser/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_PRINT):		print/obj/%.o : print/%.c
						@ mkdir -p print/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJECTS_SIGNAL):		signal/obj/%.o : signal/%.c
						@ mkdir -p signal/obj
						@ gcc $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
						@ rm -rf $(OBJECTS) $(OBJECTS_BUILT) $(OBJECTS_CLEAN) $(OBJECTS_EXECUTER) $(OBJECTS_EXPANDER) $(OBJECTS_INIT) $(OBJECTS_LEXER) $(OBJECTS_PARSER) $(OBJECTS_PRINT) $(OBJECTS_SIGNAL)
						@ rm -rf $(OBJECTS_DIR) $(OBJECTS_DIR_BUILT) $(OBJECTS_DIR_CLEAN)  $(OBJECTS_DIR_EXECUTER) $(OBJECTS_DIR_EXPANDER) $(OBJECTS_DIR_INIT) $(OBJECTS_DIR_LEXER) $(OBJECTS_DIR_PARSER) $(OBJECTS_DIR_PRINT) $(OBJECTS_DIR_SIGNAL)
						@ make clean -s -C $(LIBFT_PATH)

fclean:
						@ rm -rf $(OBJECTS) $(OBJECTS_BUILT) $(OBJECTS_CLEAN) $(OBJECTS_EXECUTER) $(OBJECTS_EXPANDER) $(OBJECTS_INIT) $(OBJECTS_LEXER) $(OBJECTS_PARSER) $(OBJECTS_PRINT) $(OBJECTS_SIGNAL)
						@ rm -rf $(OBJECTS_DIR) $(OBJECTS_DIR_BUILT) $(OBJECTS_DIR_CLEAN)  $(OBJECTS_DIR_EXECUTER) $(OBJECTS_DIR_EXPANDER) $(OBJECTS_DIR_INIT) $(OBJECTS_DIR_LEXER) $(OBJECTS_DIR_PARSER) $(OBJECTS_DIR_PRINT) $(OBJECTS_DIR_SIGNAL)
						@ rm -rf $(NAME) $(MINISHELL) $(LIBFT)
						@ make fclean -s -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
