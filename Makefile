# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#              #
#    Updated: 2024/11/15 19:20:50 by ele-borg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

SRC_FILES = main.c \
			parsing.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = philo

FLAGS = -Wall -Wextra -Werror -pthread -g3 -I.

CC = cc

#rules

all: ${NAME} 

${NAME}: ${OBJ_FILES}
	${CC} ${FLAGS} ${OBJ_FILES} -o ${NAME}

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

clean: 
	rm  -f ${OBJ_FILES}

fclean: clean
	rm -f ${NAME}

re: fclean all

reclean : all clean

.PHONY: all clean fclean re