/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:45:17 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/01 18:41:16 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define ERROR 0 /* exit with error message */
# define NOTHING 1 /* exit without error message */

# define SORTED 0 /* a-stack is sorted */
# define NOT_SORTED 1 /* a-stack isn't sorted */

# define ONLY 0 /* operate instructions at a stack */
# define BOTH 2 /* operate instructions both a and b stack */

# define ZERO_TRIANGLE 0 /* have no triangles */
# define KEEP_NB 0 /* when use keeping number of top or bottom section */

# define SRC_BOT 0
# define SRC_TOP 1
# define DST_BOT 2

typedef struct s_stack
{
	int		*arr;
	int		top;
	char	name;
}	t_stack;

typedef struct s_values
{
	int	*args;
	int	*copy;
	int	tmp[3];
	int	one_third;
	int	status;
	int	res;
}	t_values;

/* push_swap.c - including main function */
int			parse_argv(t_stack *a, char *argv);
void		move_b_to_a(t_stack *src, t_stack *dst, t_values *values);
long long	ft_atoll(t_stack *a, const char *str);

/* error_check.c - including funcs to check error */
void		check_sort(t_stack *a);
void		free_and_null(int **ptr);
void		detect_duplicates(t_stack *a);
void		error_and_exit(int *arr, int flag);

/* sort_below_five.c - including funcs to sort a's size below 5 */
int			find_min(t_stack *a);
void		sort_below_five(t_stack *a, t_stack *b);
void		sort_below_four(t_stack *a, t_stack *b);
void		sort_below_three(t_stack *a, t_stack *b);
void		sort_below_two(t_stack *a, t_stack *b);

/* operators.c - including funcs to need to operate instructions */
void		do_operation(t_stack *a, t_stack *b);
void		push(t_stack *src, t_stack *dst);
void		swap(t_stack *src, t_stack *dst, int flag);
void		rotate(t_stack *src, t_stack *dst, int flag);
void		reverse_rotate(t_stack *src, t_stack *dst, int flag);

/* merge_sort.c */
void		merge_sort(t_stack **src, t_stack **dst, t_values *values);
void		merge(t_stack *src, t_stack *dst, t_values *values, int idx);
void		reverse_merge(t_stack *src, t_stack *dst, t_values *values, \
																	int idx);
void		divide(t_stack *src, t_stack *dst, t_values *values, int depth);
void		move_one_third(t_stack **src, t_stack **dst, t_values *values, \
																int triangle);

/* utils_one.c - including funcs to return useful values */
int			get_depth(int nb);
int			get_order(int idx);
int			power(int base, int exp);
int			is_empty(t_values *values, int idx);
void		ret_one_third(t_values *values, int triangle);

/* utils_two.c - */
int			find_merge_max(t_stack *src, int start, int cnt);
int			find_merge_min(t_stack *src, int start, int cnt);
int			set_max(t_stack *src, t_stack *dst, t_values *values);
int			set_min(t_stack *src, t_stack *dst, t_values *values);
void		put_tmp(t_values *values, int triangle, int idx);

/* make_triangle.c */
void		make_triangle(t_stack *src, t_stack *dst, t_values *values, int nb);
void		make_rev_triangle(t_stack *src, t_stack *dst, t_values *values, \
																		int nb);
void		handle_top(t_stack *src, t_stack *dst, int idx, int flag);
void		handle_bottom(t_stack *src, t_stack *dst, int idx, int flag);
void		dup_args(t_stack *src, t_stack *dst, t_values *values, int depth);

/* merge_below_six.c - including funcs to make initial triangles */
void		merge_below_six(t_stack *src, t_stack *dst);
void		merge_below_five(t_stack *src, t_stack *dst);
void		merge_below_four(t_stack *src, t_stack *dst);
void		merge_below_three(t_stack *src, t_stack *dst);
void		merge_below_two(t_stack *src, t_stack *dst);

/* rev_merge_below_six.c - including funcs to make initial reverse triangles */
void		rev_merge_below_six(t_stack *src, t_stack *dst);
void		rev_merge_below_five(t_stack *src, t_stack *dst);
void		rev_merge_below_four(t_stack *src, t_stack *dst);
void		rev_merge_below_three(t_stack *src, t_stack *dst);
void		rev_merge_below_two(t_stack *src, t_stack *dst);

#endif