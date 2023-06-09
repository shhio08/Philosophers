# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stakimot <stakimot@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 19:30:41 by stakimot          #+#    #+#              #
#    Updated: 2023/06/09 09:39:51 by stakimot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
# -fsanitize=thread -g
INC			=	inc/

SRC_DIR		=	src/
OBJ_DIR		=	obj/

SRC_NAME	=	ft_atoi.c init.c main.c monitor.c philo_utils.c philo.c utils.c
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))


all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC) -c $^ -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re