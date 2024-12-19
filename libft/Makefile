
NAME = libft.a

AR = ar -rc

RM = rm -rf 

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_strlen.c ft_atoi.c ft_strcmp.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_split.c ft_putendl_fd.c \
ft_memset.c ft_bzero.c ft_calloc.c ft_isalpha.c ft_isalnum.c ft_strncmp.c ft_itoa.c

OBJ = ${SRC:.c=.o}

$(NAME): $(OBJ) libft.h
	$(AR) $(NAME) $(OBJ)

all: $(NAME)
 
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all