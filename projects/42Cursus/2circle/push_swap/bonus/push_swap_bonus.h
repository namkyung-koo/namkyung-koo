/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:45:43 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/02 08:19:04 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include <limits.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define ERROR 0 /* exit with error message */
# define NOTHING 1 /* exit without error message */
# define KO 2

# define SORTED 0 /* a-stack is sorted */
# define NOT_SORTED 1 /* a-stack isn't sorted */

# define ONLY 0 /* operate instructions at a stack */
# define BOTH 2 /* operate instructions both a and b stack */

typedef struct s_stack
{
	int		*arr;
	int		top;
	char	name;
}	t_stack;

/* push_swap_bonus.c */
int			parse_argv(t_stack *a, char *argv);
void		parse_instructions(t_stack *a, t_stack *b);
void		do_instructions(t_stack *a, t_stack *b, char *op);
long long	ft_atoll(t_stack *a, const char *str);

/* error_check_bonus.c */
void		free_and_null(int **ptr);
void		detect_duplicates(t_stack *a);
void		error_and_exit(int *arr, int flag);
void		check_sort_and_print(t_stack *a, t_stack *b);

/* operators_bonus.c */
void		do_operation(t_stack *a, t_stack *b);
void		push(t_stack *src, t_stack *dst);
void		swap(t_stack *src, t_stack *dst, int flag);
void		rotate(t_stack *src, t_stack *dst, int flag);
void		reverse_rotate(t_stack *src, t_stack *dst, int flag);

#endif