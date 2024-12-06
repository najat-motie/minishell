NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I/Users/nmotie-/.brew/opt/readline/include
 
SRC = main.c environment/utils.c environment/checks.c environment/export.c environment/unset.c environment/pwd.c \
builtin/built_in1.c builtin/built_in2.c builtin/builtin_utils1.c builtin/builtin_utils2.c builtin/handle_builtin.c \
redirections/heredoc.c redirections/expand.c redirections/expand_utils1.c \
redirections/expand_utils2.c redirections/open_files.c redirections/redirects.c \
execute/exec.c execute/path.c execute/utils.c execute/signals.c \
parsing/create.c parsing/utils.c parsing/clear.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) minishell.h
	make -C libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline libft/libft.a -L/Users/nmotie-/.brew/opt/readline/lib -o minishell

all: $(NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all