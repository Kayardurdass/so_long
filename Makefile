SRCS := $(wildcard ./src/*.c)
OBJDIR = obj
OBJS = ${SRCS:./src/%.c=./$(OBJDIR)/%.o}
NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft
INCLUDE = -I./include -I./libft  -I/usr/include -Imlx_linux
LINKER = -L$(LIBFT_DIR) -lft -L./minilibx-linux/ -lmlx -lXext -lX11 -lm -lbsd

YELLOW = \033[33m
GREEN = \033[32m
CYAN = \033[36m
RESET = \033[0m
RED = \033[31m

all: $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -sC $(LIBFT_DIR)
	@echo "$(GREEN)Build successful!$(RESET)"

norm:
	@norminette $(SRCS) > /dev/null && echo "$(GREEN)Norminette: OK$(RESET)" || ( echo "$(RED)Norminette: KO" && norminette $(SRCS) | cat)

minilibx-linux/libmlx.a:
	@make -sC minilibx-linux/ > /dev/null 2> /dev/null

$(NAME): minilibx-linux/libmlx.a $(LIBFT) $(OBJS) 
	@cat .title | python .lolcat
	@echo "$(YELLOW)Executing norminette on src$(RESET)"
	@make -s norm
	@echo "$(YELLOW)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) ./GNL/get_next_line.c   -o $(NAME) $(LINKER)
	@echo "$(GREEN)Build successful!$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: ./src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "$(GREEN)Cleaning up...$(RESET)"
	@rm -f $(OBJS)
	@make clean -sC $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all clean fclean re
