# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 17:58:52 by abaryshe          #+#    #+#              #
#    Updated: 2025/04/12 04:26:45 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CMPFLAGS = -Wall -Wextra -Werror
HEADER = libft.h
SOURCES = ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c
OBJECTS = ${SOURCES:.c=.o}
FREM = rm -f

all: ${NAME}

${NAME}: ${OBJECTS}
	ar rcs ${NAME} ${OBJECTS}

%.o: %.c
	${CC} ${CMPFLAGS} -I ${HEADER} -c $< -o $@

clean:
	${FREM} ${OBJECTS}

fclean: clean
	${FREM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
