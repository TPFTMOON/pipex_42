# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 09:28:27 by abaryshe          #+#    #+#              #
#    Updated: 2025/04/12 10:39:31 by abaryshe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

INC_DIR = pipex_project/includes
OBJ_DIR = objects
BONUS_OBJ_DIR = objects_bonus
LIBFT_DIR = libft
PRINTF_DIR = ft_printf
FREM = rm -f

CC = cc
CMPFLAGS = -Wall -Wextra -Werror
INCLUDES = -I ${INC_DIR} -I ${LIBFT_DIR} -I ${PRINTF_DIR}

SRCS_DIR = pipex_project/sources/pipex_srcs
PIPEX_SRCS = pipex.c pipex_errors_and_free.c pipex_utils.c pipex_files.c pipex_parent.c pipex_child.c
SRCS = $(addprefix ${SRCS_DIR}/, ${PIPEX_SRCS})
OBJS = $(addprefix ${OBJ_DIR}/, $(notdir ${SRCS:.c=.o}))

BONUS_SRCS_DIR = pipex_project/sources/pipex_srcs_bonus
BONUS_PIPEX_SRCS = pipex_bonus.c pipex_errors_and_free_bonus.c pipex_utils_bonus.c pipex_files_bonus.c pipex_parent_bonus.c pipex_child_bonus.c
BONUS_SRCS = $(addprefix ${BONUS_SRCS_DIR}/, ${BONUS_PIPEX_SRCS})
BONUS_OBJS = $(addprefix ${BONUS_OBJ_DIR}/, $(notdir ${BONUS_SRCS:.c=.o}))

LIBFT = ${LIBFT_DIR}/libft.a
PRINTF = ${PRINTF_DIR}/libftprintf.a

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT} ${PRINTF}
	${CC} ${CMPFLAGS} ${INCLUDES} ${OBJS} ${LIBFT} ${PRINTF} -o ${NAME}

#OBJS:
${OBJ_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

${LIBFT}:
	$(MAKE) -C ${LIBFT_DIR}

${PRINTF}:
	$(MAKE) -C ${PRINTF_DIR}

clean:
	${FREM} ${OBJS}
	${FREM} -d ${OBJ_DIR}
	${FREM} ${BONUS_OBJS}
	${FREM} -d ${BONUS_OBJ_DIR}
	${MAKE} -C ${LIBFT_DIR} clean
	${MAKE} -C ${PRINTF_DIR} clean

fclean: clean
	${FREM} ${NAME}
	${FREM} ${BONUS_NAME}
	${MAKE} -C ${LIBFT_DIR} fclean
	${MAKE} -C ${PRINTF_DIR} fclean

re: fclean all

bonus: ${BONUS_NAME}

${BONUS_NAME}: ${BONUS_OBJS} ${LIBFT} ${PRINTF}
	${CC} ${CMPFLAGS} ${INCLUDES} ${BONUS_OBJS} ${LIBFT} ${PRINTF} -o ${BONUS_NAME}

#BONUS_OBJS:
${BONUS_OBJ_DIR}/%.o: ${BONUS_SRCS_DIR}/%.c
	@mkdir -p ${BONUS_OBJ_DIR}
	${CC} ${CMPFLAGS} ${INCLUDES} -c $< -o $@

debug:	 ${OBJS} ${LIBFT} ${PRINTF}
		${CC} ${CMPFLAGS} -g ${INCLUDES} ${SRCS} ${LIBFT} ${PRINTF} -o ${NAME}

.PHONY: all clean fclean re bonus debug
