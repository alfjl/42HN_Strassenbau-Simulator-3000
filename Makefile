NAME := cub3d
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR = ./inc/
# ifdef BONUS
# HEADER_DIR = ./inc/bonus/
# endif

# $(NAME): HEADER_DIR = ./inc/
# bonus: HEADER_DIR = ./inc/bonus/
SRCS :=	config_header_parse.c \
		config_header_validate.c \
		config_map_parse_1.c \
		config_map_parse_2.c \
		config_map_validate_1.c \
		config_map_validate_2.c \
		config_map_validate_3.c \
		config.c \
		controls_keyboard.c \
		controls_mouse.c \
		data_utils_1.c \
		data_utils_2.c \
		data.c \
		doors.c \
		exit.c \
		floor_and_ceiling.c \
		fps_bonus.c \
		frame.c \
		free.c \
		images.c \
		main.c \
		minimap.c \
		mlx.c \
		player_movement.c \
		player.c \
		rays_calculate_horizontal.c \
		rays_calculate_vertical.c \
		rays.c \
		reader_1.c \
		reader_2.c \
		reader_3.c \
		reader_4.c \
		sky.c \
		sprites.c \
		stringbuilder_1.c \
		stringbuilder_2.c \
		temp_buffer.c \
		textures.c \
		utils_1.c \
		utils_2.c \
		utils_3.c \
		utils_4.c \
		utils_colors.c \
		utils_mlx_platform_1.c \
		utils_mlx_platform_2.c \
		utils_mlx_re.c \
		utils_mlx.c \
		validation_utils.c \
		walls_vertical_line.c \
		walls.c
OBJS := $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
HEADERS = $(wildcard $(HEADER_DIR)*.h)
PLATFORM := $(shell uname -s)
CC := gcc
CFLAGS = -g -Wall -Wextra -Werror
ifeq ($(DEBUG),1)
CFLAGS += -D DEBUG=1
else
CFLAGS += -D DEBUG=0
endif
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m
LIBFT_DIR := ./libft/
LIBFT_INCLUDE_PATH := $(LIBFT_DIR)inc/
LIBFT := $(LIBFT_DIR)libft.a
ifeq ($(PLATFORM), Linux)
MLX_DIR := ./mlx_linux/
MLX_FLAGS := -lXext -lX11 -lm -lz -lXrender
else
MLX_DIR := ./mlx_mac_stable/
MLX_FLAGS := -framework OpenGL -framework AppKit
endif
MLX_INCLUDE_PATH := $(MLX_DIR)
MLX := $(MLX_DIR)libmlx.a
INCLUDES = -I $(HEADER_DIR) -I $(LIBFT_INCLUDE_PATH) -I $(MLX_INCLUDE_PATH)
DEPS = $(LIBFT) $(MLX) $(HEADERS)
MAKEFLAGS += --no-print-directory

all: extern $(NAME)

extern:
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $@
	@echo "\n$(GREEN)$(NAME) created$(NC)"
	@echo "$(YELLOW)SUCCESFULLY COMPILED!$(NC)"
#	@echo name: $(DEPS)
#	@echo name: $(INCLUDES)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

# bonus: set all
# 	@echo bonus: $(DEPS)

# bonus:
# 	@make BONUS=1

# set:
# 	@touch $(HEADERS)
# 	$(eval HEADER_DIR = ./inc/bonus/)

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

norm:
	@norminette $(SRC_DIR)* $(HEADER_DIR)*

.INTERMEDIATE: ofilemessage

.PHONY: clean fclean all re
