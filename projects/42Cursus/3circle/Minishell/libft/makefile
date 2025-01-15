# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/02 10:07:49 by euiclee           #+#    #+#              #
#    Updated: 2023/02/24 13:31:17 by euiclee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)

INCLUDE_DIR = ./includes/

SRCS_DIR = ./srcs/
SRCS =  get_next_line.c ft_atoi.c ft_isalpha.c ft_itoa.c ft_lstdelone.c \
		ft_strmapi.c ft_strstr.c ft_toupper.c ft_atod.c ft_isalnum.c \
		ft_split.c ft_strdup.c ft_strlcat.c ft_strncmp.c ft_strtrim.c \
		ft_strlcpy.c ft_strnstr.c ft_substr.c ft_bzero.c ft_isascii.c \
		ft_memchr.c ft_memset.c ft_putstr_fd.c ft_strcmp.c ft_strjoin.c \
		ft_strchr.c ft_striteri.c ft_strlen.c ft_strrchr.c ft_tolower.c \
		ft_lstnew.c ft_memcpy.c ft_putendl_fd.c ft_strcat.c ft_strfind.c \
		ft_isprint.c ft_lstclear.c ft_lstmap.c ft_memcmp.c ft_putchar_fd.c \
		ft_assert.c ft_calloc.c ft_isdigit.c ft_lstadd_front.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstiter.c ft_lstsize.c ft_memmove.c ft_putnbr_fd.c \
		ft_atoll.c
		
SRCS_NAME = $(addprefix $(SRCS_DIR), $(SRCS))

OBJ_DIR = objs
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS_NAME:.c=.o)))

vpath %.c $(SRCS_DIR)

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	ar rcsu $(NAME) $(OBJS)

$(OBJ_DIR) :
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re : 
	make fclean
	make all

.PHONY : all clean fclean re