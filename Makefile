NAME 			= cub3D

INCLUDES		= includes/

LIBFT_DIR		= libft/
LIBFT_INCLUDES	= $(LIBFT_DIR)includes

SRC_DIR			= srcs/
INPUT_DIR		= $(SRC_DIR)input_validation/
RENDER_DIR		= $(SRC_DIR)render/
MINIMAP_DIR		= $(SRC_DIR)minimap/
UTILS_DIR		= $(SRC_DIR)utils/
MOVEMENT_DIR	= $(SRC_DIR)movement/

SRC_FILES		= $(SRC_DIR)main.c \
				  $(UTILS_DIR)error.c \
				  $(UTILS_DIR)utils.c \
				  $(UTILS_DIR)freeing.c \
				  $(UTILS_DIR)freeing_2.c \
				  $(INPUT_DIR)input_validation.c \
				  $(INPUT_DIR)validate_texture.c \
				  $(INPUT_DIR)validate_map.c \
				  $(INPUT_DIR)input_parsing.c \
				  $(INPUT_DIR)check_map_content.c \
				  $(INPUT_DIR)validate_borders.c \
				  $(INPUT_DIR)validate_doors.c \
				  $(RENDER_DIR)render_walls.c \
				  $(RENDER_DIR)render_walls_2.c \
				  $(MOVEMENT_DIR)movement.c \
				  $(MOVEMENT_DIR)rotation.c \
				  $(MOVEMENT_DIR)controls.c \
				  $(RENDER_DIR)textures.c \
				  $(RENDER_DIR)render_ceiling_floor.c \
				  $(RENDER_DIR)dir.c \
				  $(MINIMAP_DIR)minimap.c \
				  $(MINIMAP_DIR)doors.c \
				
OBJ_DIR			= objs/
OBJ_FILES		= $(addprefix $(OBJ_DIR), $(notdir $(SRC_FILES:.c=.o)))
 
CFLAGS			= -Wall -Wextra -Werror -Iincludes -Imlx -g
MLX_FLAGS 		= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
GCC 			= cc
RM				= rm -f

GREEN       = \033[0;92m
YELLOW 		= \033[0;33m
BLUE        = \033[0;94m
RESET       = \033[0m

all : $(OBJ_DIR) $(NAME)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT_DIR)libft.a $(OBJ_FILES)
	@$(GCC) $(CFLAGS) -o $@ $(OBJ_FILES) $(LIBFT_DIR)libft.a $(MLX_FLAGS)
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Built Cub3D executable successfully! $(RESET)\n" "Cub3D"

$(LIBFT_DIR)libft.a:
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Cub3D"

$(OBJ_DIR)%.o : $(INPUT_DIR)%.c | $(OBJ_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Cub3D"

$(OBJ_DIR)%.o : $(UTILS_DIR)%.c | $(OBJ_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Cub3D"


$(OBJ_DIR)%.o : $(RENDER_DIR)%.c | $(OBJ_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Cub3D"

$(OBJ_DIR)%.o : $(MINIMAP_DIR)%.c | $(OBJ_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Cub3D"

$(OBJ_DIR)%.o : $(MOVEMENT_DIR)%.c | $(OBJ_DIR)
	@$(GCC) $(CFLAGS) -c $< -o $@
	@printf "$(BLUE)%-10s:$(RESET) $(YELLOW)Compiled $<$(RESET)\n" "Cub3D"

clean :
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cleaned object files!$(RESET)\n" "LIBFT"
	@$(RM) -r $(OBJ_DIR)
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cleaned object files!$(RESET)\n" "Cub3D"

fclean : clean
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cleaned executables!$(RESET)\n" "LIBFT"
	@$(RM) -r $(NAME)
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cleaned executables!$(RESET)\n" "Cub3D"

re : fclean all
	@printf "$(BLUE)%-10s:$(RESET) $(GREEN)Cub3D executable rebuilt!$(RESET)\n" "Cub3D"

.PHONY: all bonus clean fclean re