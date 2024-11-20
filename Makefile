NAME = minishell

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I/Users/nmotie-/.brew/opt/readline/include
 
SRC = execute/main.c envirenment/env.c envirenment/env_utils.c envirenment/export.c \
envirenment/export_utils.c envirenment/unset.c envirenment/pwd_update.c envirenment/pwd_utils.c \
builtin/built_in.c builtin/builtin_utils1.c builtin/builtin_utils2.c builtin/handle_builtin.c \
redirections/redirects.c execute/parsing.c execute/exec.c  execute/signals.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) minishell.h
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline -lncurses ./libft/libft.a -L/Users/nmotie-/.brew/opt/readline/lib -o minishell

all: $(NAME)

clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


-I./printf : for include directories where header files are stored
-L./printf : for library directories
-llibftprintf.a : for linking a specific library
CFLAGS : compiling flags
LDFLAGS : linking flags
make -C : Change to DIRECTORY before doing anything.