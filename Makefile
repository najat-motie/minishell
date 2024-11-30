NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I/Users/nmotie-/.brew/opt/readline/include
 
SRC = main.c execution/envirenment/utils.c execution/envirenment/checks.c execution/envirenment/export.c execution/envirenment/unset.c execution/envirenment/pwd_update.c \
execution/builtin/built_in1.c execution/builtin/built_in2.c execution/builtin/builtin_utils1.c execution/builtin/builtin_utils2.c execution/builtin/handle_builtin.c \
execution/redirections/heredoc.c execution/redirections/expand.c execution/redirections/expand_utils1.c \
execution/redirections/expand_utils2.c execution/redirections/open_files.c execution/redirections/redirects.c \
execution/execute/exec.c execution/execute/path.c execution/execute/utils.c execution/execute/signals.c \
parsing/create.c parsing/utils.c parsing/clear.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) minishell.h
	make -C execution/libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline execution/libft/libft.a -L/Users/nmotie-/.brew/opt/readline/lib -o minishell

all: $(NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all