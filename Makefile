NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I/Users/nmotie-/.brew/opt/readline/include

SRC = main.c \
parsing/utils/free.c parsing/utils/list_cmd.c parsing/utils/list_token.c parsing/utils/list_utils.c parsing/utils/ms_utils.c \
parsing/parse/check_quote.c parsing/parse/create_cmd_fd.c parsing/parse/create_cmd_param.c parsing/parse/parse_line.c parsing/parse/create_here_fd.c\
parsing/parse/create_cmd.c parsing/parse/create_token.c parsing/parse/dollar_handle.c parsing/parse/dollar_replace.c parsing/parse/exit_env.c parsing/utils/init.c \
parsing/heredoc/expand_utils1.c parsing/heredoc/expand_utils2.c parsing/heredoc/expand.c parsing/heredoc/heredoc.c \
execution/environ/utils.c execution/environ/checks.c execution/environ/export.c execution/environ/unset.c \
execution/environ/pwd.c execution/environ/env.c execution/builtin/built_in1.c execution/builtin/built_in2.c \
execution/execute/fds.c execution/builtin/builtin_utils1.c execution/builtin/builtin_utils2.c execution/builtin/handle_builtin.c \
execution/execute/exec.c execution/execute/path.c execution/execute/utils.c execution/execute/signals1.c execution/execute/signals2.c

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