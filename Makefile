# ==============================================================================
#                                     CONFIG
# ==============================================================================

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes
MLX_DIR     = minilibx

# Source Files (Add your specific files here)
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
    INCLUDES    = -I$(INC_DIR) -I$(MLX_DIR) -I/usr/include
else
    # macOS flags: requires OpenGL and AppKit frameworks
    MLX_LIB     = $(MLX_DIR)/libmlx.a
    MLX_FLAGS   = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    INCLUDES    = -I$(INC_DIR) -I$(MLX_DIR)
endif

# ==============================================================================
#                                     RULES
# ==============================================================================

all: $(MLX_LIB) $(NAME)

# Compile the executable
$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) built successfully!"

# Compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile MinilibX if not built
$(MLX_LIB):
	@echo "Compiling MinilibX..."
	@make -C $(MLX_DIR)

# ==============================================================================
#                                   CLEANUP
# ==============================================================================

clean:
	@echo "Cleaning object files..."
	rm -rf $(OBJ_DIR)
	@make clean -C $(MLX_DIR)

fclean: clean
	@echo "Cleaning executable..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re