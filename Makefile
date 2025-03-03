# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#              #
#    Updated: 2025/02/28 13:00:24 by ele-borg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

SRC_DIR = sources
OBJ_DIR = objets

SRC_FILES = ${SRC_DIR}main.c \
			${SRC_DIR}synchronisation.c \
			${SRC_DIR}init.c \
			${SRC_DIR}parsing.c \
			${SRC_DIR}simulation_dinner.c \
			${SRC_DIR}utils.c \
			${SRC_DIR}libft.c \
			${SRC_DIR}monitor.c \

OBJ_FILES =	$(OBJ_DIR)/main.o \
			$(OBJ_DIR)/synchronisation.o \
			$(OBJ_DIR)/init.o \
			$(OBJ_DIR)/parsing.o \
			$(OBJ_DIR)/simulation_dinner.o \
			$(OBJ_DIR)/utils.o \
			$(OBJ_DIR)/libft.o \
			$(OBJ_DIR)/monitor.o \

NAME = philo

# FLAGS_C = -Wall -Wextra -Werror -pthread -fsanitize=thread -I.
FLAGS_C = -Wall -Wextra -Werror -pthread  -I.

# FLAGS_L = -fsanitize=thread

NAME = philo

CC = cc

#rules

all: ${NAME}

${NAME}: ${OBJ_FILES}
	${CC} ${FLAGS_L} ${OBJ_FILES} -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	$(CC) -c $(FLAGS_C) $< -o $@

clean:
	rm  -f ${OBJ_FILES}

fclean: clean
	rm -f ${NAME}

re: fclean all

reclean : all clean

.PHONY: all clean fclean re
