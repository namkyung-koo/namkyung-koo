CFLAGS = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit
NAME = fractol
INCS = includes
SRCS = main.c parsing.c pixeling.c fractal_set.c hooking_key.c utils.c utils2.c hooking_mouse.c

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -I $(INCS) -o $@

all : $(NAME)

clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re :
	@make fclean
	@make all

bonus : $(NAME)

.PHONY : all clean fclean re bonus