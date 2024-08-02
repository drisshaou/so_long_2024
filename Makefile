# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drhaouha <drhaouha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 22:11:56 by drhaouha          #+#    #+#              #
#    Updated: 2024/08/02 08:22:14 by drhaouha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLUE			=	\033[0;34m
GREEN			=	\033[0;32m
ORANGE			=	\033[0;33m
RED				=	\033[0;31m
NC				=	\033[0m

CC			= cc

CFLAGS		= -Wall -Werror -Wextra -g

NAME		= so_long

SRC_NAME	=	check_map.c flood_n_free.c parse_n_check.c \
				add_all_images2.c draw_frame2.c draw_frame.c \
				free_all.c game_loop.c key_release.c \
				set_grounds2.c you_win.c add_all_images.c \
				draw_frame3.c exit_game.c game_loop2.c \
				game_over.c malloc_game2.c set_grounds.c \
				center_player_in_window.c draw_frame4.c free_all2.c \
				game_loop3.c init_window_n_players.c malloc_game.c \
				try_game.c main.c

OBJ_PATH	= objs

PARSE_PATH	= ./parsing
GAME_PATH	= ./game

OBJ_NAME	= ${SRC_NAME:.c=.o}

FTMINI_DIR	= ./libftmini
MINIFT_LIB	= $(addprefix ${FTMINI_DIR}/,libftmini.a)
MINIFT_INC	= -I ${FTMINI_DIR}
MINIFT_LNK	= -L ${FTMINI_DIR} -lftmini

MLX_DIR		= ./minilibx
MLX_LIB		= $(addprefix ${MLX_DIR}/,libmlx_Linux.a)
MLX_INC		= -I ${MLX_DIR}
MLX_LNK		= -L ${MLX_DIR} -lmlx_Linux

GFLAGS		= -lXext -lX11 -lm -lbsd

INC			= -I ./include

OBJ			= $(addprefix ${OBJ_PATH}/,${OBJ_NAME})


all: objs libftmini libmlx ${NAME}

${NAME}: ${OBJ} ${MINIFT_LIB} ${MLX_LIB}
					@${CC} ${CFLAGS} $^ ${INC} ${MINIFT_LNK} ${MINIFT_INC} ${MLX_LNK} ${MLX_INC} ${GFLAGS} -o $@
					@echo "[${GREEN}so_long${NC}] : Executable created.${NC}"

${OBJ_PATH}/%.o: ${GAME_PATH}/%.c
					@${CC} ${CFLAGS} ${INC} ${MINIFT_INC} ${MLX_INC} -c $< -o $@

${OBJ_PATH}/%.o: ${PARSE_PATH}/%.c
					@${CC} ${CFLAGS} ${INC} ${MINIFT_INC} ${MLX_INC} -c $< -o $@

${OBJ_PATH}/%.o: %.c
					@${CC} ${CFLAGS} ${INC} ${MINIFT_INC} ${MLX_INC} -c $< -o $@

objs:
			@mkdir ${OBJ_PATH}
			@echo "[${BLUE}so_long${NC}] : Directory objs created.${NC}"
libmlx:
			@make -isC ${MLX_DIR}

libftmini:
			@make -isC ${FTMINI_DIR}

clean:
			@make -isC ${MLX_DIR} clean
			@make -isC ${FTMINI_DIR} fclean
			@rm -rf ${OBJ_PATH}
			@echo "[${ORANGE}so_long${NC}] : Archives and directory objs removed.${NC}"

fclean: clean
			@rm -f ${NAME}
			@echo "[${RED}so_long${NC}] : Executable removed${NC}"

re: fclean all

.PHONY:		fclean clean re all libftmini