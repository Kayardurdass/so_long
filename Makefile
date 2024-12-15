SRCS = $(wildcard *.c GNL/*.c)

OBJ = $(SRCS:.c=.o)

NAME = so_long

CC ?= clang
MLX_PATH := ./minilibx-linux
MLX_LIB := -L$(MLX_PATH) -lmlx
CFLAGS = #-Wall -Werror -Wextra
DEPS := ${SRCS:.c=.d}

%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o ${<:.c=.o}

${NAME}: $(OBJ)
	cc ${CFLAGS} ${OBJ} $(MLX_LIB) -I$(MLX_PATH) -Llibft/  -g -lft -lXext -lX11 -lm -lbsd -o $(NAME)

all: 	${NAME}

clean:	
		rm -f ${OBJ}

fclean:	clean;
		rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re
