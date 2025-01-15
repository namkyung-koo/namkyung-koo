NAME = minishell
CFLAGS = -I $(INCLUDES) -MMD -Wall -Wextra -Werror
RFLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib -I${HOME}/.brew/opt/readline/include

SRCS_PARSE = $(addprefix parse/, parse_env.c parse_exit.c parse_quote.c parse_redir.c parse_split.c parse_tokens.c parse.c parse_expand.c)
SRCS_BUILTIN = $(addprefix builtin/, cd.c env.c export.c pwd.c unset.c echo.c exit.c builtin_utils.c)
SRCS_EXECUTE = $(addprefix execute/, here_doc.c pipex.c execute.c utils.c builtin.c redirect.c signal.c syntax.c cmd.c)

SRCS_DIR = ./srcs/
SRCS = main.c $(SRCS_PARSE) $(SRCS_BUILTIN) $(SRCS_EXECUTE)
SRCS_NAME = $(addprefix $(SRCS_DIR), $(SRCS))

INCLUDES = ./includes/
SHELL = bash

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_NAME:.c=.o)))

DEPS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_NAME:.c=.d)))

vpath %.c $(SRCS_DIR) $(SRCS_DIR)parse/ $(SRCS_DIR)builtin/ $(SRCS_DIR)execute/

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJS)
	@echo -n "Making minishell... "
	@make all -s -C libft
	@cc -g $(OBJS) $(RFLAGS) ./libft/libft.a -o $@ 
	@echo -e "\033[32;1m"complete"\033[0m"
	@sleep 0.2

$(OBJ_DIR) :
	@mkdir $@

$(OBJ_DIR)/%.o : %.c
	@cc -g $(CFLAGS) -I${HOME}/.brew/opt/readline/include -c $< -o $@

clean :
	@echo -n "Deleting object files : "
	@make clean -s -C libft
	@rm -rf $(OBJ_DIR)
	@echo -e "\033[31;1m"delete"\033[0m"
	@sleep 0.2

fclean : clean
	@echo -n "Deleting minishell : "
	@make fclean -s -C libft
	@rm -f minishell
	@echo -e "\033[31;1m"delete"\033[0m"
	@sleep 0.2

re : 
	@make fclean
	@make all

.PHONY : all clean fclean re

-include $(DEPS)