NAME = cub3D

CFLAGS = -I $(INC_DIR) -Wall -Wextra -Werror -MMD -MP
CLIB = -lmlx -Lmlx -framework OpenGL -framework Appkit

INC_DIR = ./inc/

SRCS_PARSE = $(addprefix parse/, utils.c file_validation.c identifier_part.c map_part.c middle_part.c set_value_utils.c)
SRCS_RENDER = $(addprefix render/, calculate_wall.c load_texture.c main_loop.c raycasting.c select_texture.c set_info.c draw.c key_left_right.c key_player.c)

SRCS_BNS_PARSE = $(addprefix parse/, utils_bonus.c file_validation_bonus.c identifier_part_bonus.c map_part_bonus.c middle_part_bonus.c set_value_utils_bonus.c)
SRCS_BNS_RENDER = $(addprefix render/, calculate_wall_bonus.c load_texture_bonus.c main_loop_bonus.c raycasting_bonus.c select_texture_bonus.c set_info_bonus.c draw_bonus.c key_left_right_bonus.c key_player_bonus.c)

SRC_DIR = ./src/
SRC_BNS_DIR = ./src_bonus/

SRCS = main.c $(SRCS_PARSE) $(SRCS_RENDER)
SRCS_BNS = main_bonus.c $(SRCS_BNS_PARSE) $(SRCS_BNS_RENDER)

SRCS_NAME = $(addprefix $(SRC_DIR), $(SRCS))
SRCS_BNS_NAME = $(addprefix $(SRCS_BNS_DIR), $(SRCS_BNS))

OBJ_DIR = obj

ifndef WITH_BONUS
	OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_NAME:.c=.o)))
	DEPS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_NAME:.c=.d)))
	vpath %.c $(SRC_DIR) $(SRC_DIR)parse/ $(SRC_DIR)render/
else
	OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_BNS_NAME:.c=.o)))
	DEPS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_BNS_NAME:.c=.d)))
	vpath %.c $(SRC_BNS_DIR) $(SRC_BNS_DIR)parse/ $(SRC_BNS_DIR)render/
endif

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	make bonus -s -C libft
	make all -s -C mlx
	$(CC) $(CFLAGS) $(CLIB) $(OBJS) ./libft/libft.a -o $@

$(OBJ_DIR) :
	mkdir $@

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus :
	@make WITH_BONUS=1 all

clean :
	make clean -s -C libft
	make clean -s -C mlx
	rm -rf $(OBJ_DIR)

fclean : clean
	make fclean -s -C libft
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re

-include $(DEPS)