NAME := cub3d
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR := ./inc/
SRCS :=	main.c \
		exit.c \
		frame_loop.c \
		images.c \
		map.c \
		micromap.c \
		mlx.c \
		player_movement.c \
		rays_calculate_horizontal.c \
		rays_calculate_vertical.c \
		rays.c \
		textures.c \
		utils_colors.c \
		utils_mlx_re.c \
		utils_mlx.c \
		utils.c \
		walls_vertical_line.c \
		walls.c \
		fps.c #remove
OBJS := $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
HEADERS := $(HEADER_DIR)*.h
CC := gcc
CFLAGS := -g -Wall -Wextra -Werror
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m
LIBFT_DIR := ./libft/
LIBFT_INCLUDE_PATH := $(LIBFT_DIR)/inc/
LIBFT := $(LIBFT_DIR)libft.a
LIBFT_OBJS := $(LIBFT_DIR)obj/*.o
MLX_DIR := ./mlx/
MLX_INCLUDE_PATH := $(MLX_DIR)
MLX := $(MLX_DIR)libmlx.a
MLX_FLAGS := -lXext -lX11 -lm -lz -lXrender
INCLUDES := -I $(HEADER_DIR) -I $(LIBFT_INCLUDE_PATH) -I $(MLX_INCLUDE_PATH)
DEPS := $(LIBFT) $(MLX) $(HEADERS)
MAKEFLAGS += --no-print-directory

all: link $(NAME)

link:
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@
	@echo "\n$(GREEN)$(NAME) created$(NC)"
	@echo "$(YELLOW)SUCCESFULLY COMPILED!$(NC)"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

ofilemessage:
	@echo "compiling $(NAME)-object-files: \c"

clean:
	@rm -rf $(OBJS) *.dSYM
	@echo "$(RED)$(NAME)-object-files deleted$(NC)"
	@echo "$(RED)$(NAME)-dSYM-files deleted$(NC)"
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(NC)"
	@$(MAKE) xclean -C $(LIBFT_DIR)

re: fclean all

peace:
	@echo "\n"
	@echo "     .''.    .',"
	@echo "     |  |   /  /"
	@echo "     |  |  /  /"
	@echo "     |  | /  /"
	@echo "     |  |/  ;-._"
	@echo "     }  \` _/  / ;"
	@echo "     |  /\` ) /  /"
	@echo "     | /  /_/\_/\ "
	@echo "     |/  /      |"
	@echo "     (  ' \ '-  |"
	@echo "      \    \`.  /"
	@echo "       |      |"
	@echo "       |      |\n"

.INTERMEDIATE: ofilemessage

.PHONY: clean fclean all re link