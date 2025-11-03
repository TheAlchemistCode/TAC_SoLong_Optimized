# Program name
NAME := so_long

# Compiler and flags
CC   := cc
CFLAGS := -Wall -Wextra -Werror -Iinclude -Iminilibx-linux

# Libft configuration
LIBFT_DIR := ./libft
LIBFT_LIB := $(LIBFT_DIR)/libft.a
LIBFT_LNK := -L$(LIBFT_DIR) -lft

# MiniLibX configuration
MLX_DIR := ./minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
# Link MiniLibX with required X11 libraries
MLX_LNK := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Source files (relative to src/ directory)
SRC_FILES := main.c map_parse.c map_validation.c \
			 validation/map_components.c validation/map_structure.c \
			 validation/map_pathfinding.c validation/map_path_utils.c \
			 validation/map_flood_fill.c \
			 graphics/init_graphics.c graphics/textures.c graphics/render.c \
			 graphics/input_handler.c graphics/movement.c graphics/cleanup.c \
			 graphics/player_sprite.c graphics/level_management.c \
			 graphics/level_setup.c \
			 combat/attack_system.c combat/attack_helpers.c \
			 enemy/enemy_init.c enemy/enemy_update.c enemy/enemy_render.c \
			 enemy/enemy_movement_patrol.c enemy/enemy_movement_direction.c \
			 enemy/enemy_validation.c enemy/enemy_cleanup.c \
			 animation/animation_system.c \
			 utils/timer.c

# Add src/ prefix to all source files
SRC := $(addprefix src/, $(SRC_FILES))

# Convert src/*.c paths to obj/*.o paths
OBJ := $(patsubst src/%.c,obj/%.o,$(SRC))

# Default target: build the executable
all: $(NAME)

# Link all object files and libraries to create the executable
$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LNK) $(LIBFT_LNK) -o $(NAME)

# Compile each .c file in src/ to .o file in obj/ (maintaining subdirectory structure)
obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build MiniLibX if not already built
$(MLX_LIB):
	@if [ ! -f $(MLX_LIB) ]; then \
		echo "Building MiniLibX..."; \
		cd $(MLX_DIR) && chmod +x configure && ./configure && make -f Makefile.gen; \
	fi

# Build libft library
$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

# Remove object files but keep executables and libraries
clean:
	rm -rf obj
	find src -type f -name "*.o" -delete
	$(MAKE) -C $(LIBFT_DIR) clean

# Remove everything (object files, executables, and libraries)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(MLX_DIR)/Makefile.gen $(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Linux.a

# Rebuild everything from scratch
re: fclean all

# valgrind --leak-check=full ./so_long maps/invalid_map.ber

