# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nmotie- <nmotie-@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 17:46:59 by nmotie-           #+#    #+#              #
#    Updated: 2024/11/24 14:31:15 by nmotie-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf 

AR = ar -rc

SRC = ft_strlen.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_split.c


OBJ = ${SRC:.c=.o}

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
 
clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all