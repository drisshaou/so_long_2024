# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 22:11:56 by drhaouha          #+#    #+#              #
#    Updated: 2024/07/29 13:08:30 by drhaouha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN			=	\033[0;32m
ORANGE			=	\033[0;33m
RED				=	\033[0;31m
NC				=	\033[0m

SRCS			=	get_next_line.c \
					get_next_line_utils.c \
					utils.c \
					utils2.c

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

HEADER			=	libftmini.h

OBJS			=	${SRCS:.c=.o}

NAME			=	libftmini.a

%.o: %.c
			@${CC} ${CFLAGS} -c -I./ $< -o $@
			@echo "${NC}$@ is created${NC}"

${NAME}:	${OBJS}
			@ar rcs $@ ${OBJS}
			@echo "${GREEN}${NAME} is created.${NC}"

all:		${NAME}

clean:
			@rm -f ${OBJS}
			@echo "${ORANGE}Objects of libftmini are removed.${NC}"

fclean:		clean
			@rm -f ${NAME}
			@echo "${RED}${NAME} is removed.${NC}"

re:			fclean ${NAME}

.PHONY:		fclean clean re all