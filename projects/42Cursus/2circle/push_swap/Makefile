CFLAGS = -Wall -Wextra -Werror
NAME = push_swap
CHECKER = checker
SRCS = push_swap.c error_check.c \
	   operators.c sort_below_five.c \
	   merge_sort.c make_triangle.c \
	   utils_one.c utils_two.c \
	   merge_below_six.c rev_merge_below_six.c \

SRCS_BONUS = push_swap_bonus.c error_check_bonus.c \
			 operators_bonus.c \

ifdef MAKE_CHECKER
	TARGET = $(CHECKER)
else
	TARGET = $(NAME)
endif

all : 
	@make $(TARGET)

$(NAME) : $(addprefix mandatory/, $(SRCS)) mandatory/push_swap.h
	@make -s -C libft
	$(CC) $(CFLAGS) $(addprefix mandatory/, $(SRCS)) ./libft/libft.a -o $@

$(CHECKER) : $(addprefix bonus/, $(SRCS_BONUS)) bonus/push_swap_bonus.h
	@make -s -C libft
	$(CC) $(CFLAGS) $(addprefix bonus/, $(SRCS_BONUS)) ./libft/libft.a -o $@

bonus :
	@make MAKE_CHECKER=1 all

clean :
	@make clean -C libft
	@$(RM) $(NAME)

fclean : clean
	@$(RM) $(CHECKER) ./libft/libft.a

re :
	@make fclean
	@make all

.PHONY : all bonus clean fclean re