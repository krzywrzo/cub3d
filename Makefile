# ==============================================================================
#                                     CONFIG
# ==============================================================================

NAME        = cub3D
CC          = cc
#CFLAGS      = -Wall -Wextra -Werror -g
CFLAGS		= -g

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes
MLX_DIR     = minilibx
LIBFT_DIR   = libft

# Libraries and Flags
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# Source Files
SRCS        = $(wildcard $(SRC_DIR)/*.c)
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# ==============================================================================
#                                 OS DETECTION
# ==============================================================================

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)
# Linux flags: requires -lXext -lX11 -lm
    MLX_LIB     = $(MLX_DIR)/libmlx_Linux.a
    MLX_FLAGS   = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
    INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I/usr/include
    CFLAGS      += -DLINUX=1
else
# macOS flags: requires OpenGL and AppKit frameworks
    MLX_LIB     = $(MLX_DIR)/libmlx.a
    MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
endif

# ==============================================================================
#                                     RULES
# ==============================================================================

all: $(LIBFT_LIB) $(MLX_LIB) $(NAME)

# Compile the executable
# Note: Libft flags usually come before MLX flags to avoid symbol conflicts
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) built successfully!"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile Libft
$(LIBFT_LIB):
	@echo "Compiling Libft..."
	@make -C $(LIBFT_DIR)

# Compile MinilibX
$(MLX_LIB):
	@echo "Compiling MinilibX..."
	@make -C $(MLX_DIR)

# ==============================================================================
#                                   CLEANUP
# ==============================================================================

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)

fclean: clean
	@echo "Cleaning executable..."
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
