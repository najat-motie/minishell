NAME = minishell

RM = rm -rf

CC = cc

CFLAGS = -Wall -Wextra -Werror -I/Users/nmotie-/.brew/opt/readline/include -fsanitize=address -g

SRC = main.c \
parsing/utils/free.c parsing/utils/list_cmd.c parsing/utils/list_token.c parsing/utils/list_utils.c \
parsing/utils/ms_utils.c parsing/parse/check_quote.c parsing/parse/create_cmd_param.c parsing/parse/parse_line.c \
parsing/parse/create_cmd.c parsing/parse/create_token.c parsing/parse/dollar_handle.c parsing/parse/search_env.c \
execution/redirections/expand_utils1.c execution/redirections/expand_utils2.c execution/redirections/expand.c \
execution/redirections/heredoc.c execution/redirections/open_files.c execution/redirections/redirects.c \
execution/environment/utils.c execution/environment/checks.c execution/environment/export.c \
execution/environment/unset.c execution/environment/pwd.c execution/environment/env.c \
execution/builtin/built_in1.c execution/builtin/built_in2.c execution/builtin/builtin_utils1.c \
execution/builtin/builtin_utils2.c execution/builtin/handle_builtin.c execution/execute/exec.c \
execution/execute/path.c execution/execute/utils.c execution/execute/signals.c \
execution/utils/clear.c execution/utils/free.c \

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