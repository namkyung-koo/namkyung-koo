/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:18:30 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/31 15:26:15 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_sort(t_stack **src, t_stack **dst, t_values *values)
{
	int	triangle;
	int	depth;
	int	idx;

	depth = get_depth(((*src)->top) + 1);
	while (depth >= 0)
	{
		idx = -1;
		dup_args((*src), (*dst), values, depth);
		divide((*src), (*dst), values, depth);
		triangle = power(3, depth);
		while (++idx < triangle)
		{
			if (values->status != ZERO_TRIANGLE)
				put_tmp(values, triangle, idx);
			if (get_order(idx) % 2 == 0)
				merge((*src), (*dst), values, idx);
			else
				reverse_merge((*src), (*dst), values, idx);
		}
		ret_one_third(values, triangle);
		move_one_third(src, dst, values, triangle);
		depth--;
	}
	move_b_to_a((*src), (*dst), values);
}

void	merge(t_stack *src, t_stack *dst, t_values *values, int idx)
{
	int	location;

	make_triangle(src, dst, values, values->args[idx]);
	while (values->res > 0 && values->status != ZERO_TRIANGLE)
	{
		location = set_max(src, dst, values);
		if (location == SRC_TOP)
		{
			push(src, dst);
			values->tmp[SRC_TOP]--;
		}
		else if (location == SRC_BOT)
		{
			reverse_rotate(src, dst, ONLY);
			push(src, dst);
			values->tmp[SRC_BOT]--;
		}
		else if (location == DST_BOT)
		{
			reverse_rotate(dst, src, ONLY);
			values->tmp[DST_BOT]--;
		}
		values->res--;
	}
}

void	reverse_merge(t_stack *src, t_stack *dst, t_values *values, int idx)
{
	int	location;

	make_rev_triangle(src, dst, values, values->args[idx]);
	while (values->res > 0 && values->status != ZERO_TRIANGLE)
	{
		location = set_min(src, dst, values);
		if (location == SRC_TOP)
		{
			push(src, dst);
			values->tmp[SRC_TOP]--;
		}
		else if (location == SRC_BOT)
		{
			reverse_rotate(src, dst, ONLY);
			push(src, dst);
			values->tmp[SRC_BOT]--;
		}
		else if (location == DST_BOT)
		{
			reverse_rotate(dst, src, ONLY);
			values->tmp[DST_BOT]--;
		}
		values->res--;
	}
}

void	divide(t_stack *src, t_stack *dst, t_values *values, int depth)
{
	int	triangle;
	int	tmp;
	int	i;
	int	j;

	values->args = (int *)malloc(sizeof(int) * (power(3, depth)));
	if (!values->args)
		return (free_and_null(&(src->arr)), free_and_null(&(dst->arr)));
	values->args[0] = (src->top) + 1 + (dst->top) + 1;
	triangle = 1;
	i = -1;
	while (++i < depth)
	{
		j = -1;
		while (++j < triangle)
		{
			tmp = values->args[j];
			values->args[j] = (tmp / 3);
			values->args[j + triangle] = (tmp / 3) + (tmp % 3);
			values->args[j + triangle * 2] = (tmp / 3);
		}
		triangle *= 3;
	}
}

void	move_one_third(t_stack **src, t_stack **dst, t_values *values, \
															int triangle)
{
	t_stack	*tmp;
	int		i;

	if (triangle != 1)
	{
		tmp = (*src);
		(*src) = (*dst);
		(*dst) = tmp;
	}
	i = 0;
	while (i < values->one_third)
	{
		push((*src), (*dst));
		i++;
	}
	(values->status)++;
	free_and_null((&values->copy));
}
