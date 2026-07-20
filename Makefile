NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

SRC_DIR     = src/
OBJ_DIR     = obj/
INC_DIR     = includes/
MLX_DIR     = minilibx/
LIBFT_DIR   = libft/

SRCS_FILES  = flood_fill.c \
              game_init.c \
              hooks_movement.c \
              hooks.c \
              main.c \
              parsing.c \
              player_init.c \
              raycasting_dda.c \
              raycasting_draw.c \
              raycasting_ray.c \
              raycasting_texture.c \
              textures.c \
              utils_01.c \
              utils_02.c \
              utils_03.c \
              utils_04.c \
              utils_05.c \
              utils_06.c \
              utils_07.c

SRCS        = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS        = $(addprefix $(OBJ_DIR), $(SRCS_FILES:.c=.o))

LIBFT       = $(LIBFT_DIR)libft.a

MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
INCLUDES    = -I $(INC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR) -I/usr/include

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo " $(NAME) built successfully!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@echo "Compiling MinilibX..."
	@make -C $(MLX_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
