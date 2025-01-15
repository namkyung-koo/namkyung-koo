CFLAGS = -Wall -Wextra -Werror
NAME = pipex
MNTR = mandatory
BNS = bonus
SRC = pipex.c
SRC_B = pipex_bonus.c utils_bonus.c

ifdef BONUS
	TO_COMPILE = $(addprefix $(BNS)/, $(SRC_B))
else
	TO_COMPILE = $(addprefix $(MNTR)/, $(SRC))
endif

all : $(NAME)

$(NAME) : $(TO_COMPILE)
	@make -s -C libft
	@$(CC) $(CFLAGS) $(TO_COMPILE) ./libft/libft.a -o $@

bonus :
	@make BONUS=1 all

rebonus :
	@make fclean
	@make bonus

clean :
	@make clean -C libft
	@$(RM) $(NAME)

fclean : clean
	@$(RM) ./libft/libft.a

re :
	@make fclean
	@make all

.PHONY : all bonus clean fclean re rebonus