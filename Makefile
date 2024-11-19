NAME = minishell

CC = cc

RM = rm -rf

#   export LDFLAGS="-L/Users/nmotie-/.brew/opt/readline/lib"
#   export CPPFLAGS="-I/Users/nmotie-/.brew/opt/readline/include"

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g -I/Users/nmotie-/.brew/opt/readline/include
# export LDFLAGS="-L/usr/local/opt/readline/lib"
 
# LDFLAGS = -L./printf -llibftprintf.a

# SRC = main.c utils.c exec.c free.c parsing.c redirect.c builtins.c init.c pipes.c here_doc.c env.c
SRC = main.c utils.c parsing.c env.c export.c pwd.c builtins.c redirects.c exec.c unset.c signals.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) minishell.h
	make -C ./libft
	make bonus -C ./libft
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

# -L .brew/opt/readline/lib
# -I .brew/opt/readline/include