/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:42:35 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/31 10:46:22 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_merge_max(t_stack *src, int start, int cnt)
{
	int	comp;
	int	max;
	int	idx;

	max = src->arr[start];
	comp = start + 1;
	idx = 0;
	while (idx < cnt)
	{
		if (src->top < comp)
			comp = 0;
		if (max < src->arr[comp])
			max = src->arr[comp];
		comp++;
		idx++;
	}
	return (max);
}

int	find_merge_min(t_stack *src, int start, int cnt)
{
	int	comp;
	int	min;
	int	idx;

	min = src->arr[start];
	comp = start + 1;
	idx = 0;
	while (idx < cnt)
	{
		if (src->top < comp)
			comp = 0;
		if (min > src->arr[comp])
			min = src->arr[comp];
		comp++;
		idx++;
	}
	return (min);
}

void	put_tmp(t_values *values, int triangle, int idx)
{
	int	nb;
	int	i;

	if (triangle == 1)
	{
		nb = values->args[0];
		values->tmp[0] = nb / 3;
		values->tmp[1] = nb / 3 + nb % 3;
		values->tmp[2] = nb / 3;
	}
	else
	{
		values->tmp[0] = values->copy[idx];
		values->tmp[1] = values->copy[triangle * 2 - 1 - idx];
		values->tmp[2] = values->copy[triangle * 3 - 1 - idx];
	}
	i = 0;
	while (i < 3)
	{
		values->res += values->tmp[i];
		i++;
	}
}

int	set_max(t_stack *src, t_stack *dst, t_values *values)
{
	int		max;
	int		location;

	max = INT_MIN;
	if (!is_empty(values, SRC_TOP) && max < src->arr[src->top])
	{
		max = src->arr[src->top];
		location = SRC_TOP;
	}
	if (!is_empty(values, SRC_BOT) && max < src->arr[0])
	{
		max = src->arr[0];
		location = SRC_BOT;
	}
	if (!is_empty(values, DST_BOT) && max < dst->arr[0])
	{
		max = dst->arr[0];
		location = DST_BOT;
	}
	return (location);
}

int	set_min(t_stack *src, t_stack *dst, t_values *values)
{
	int		min;
	int		location;

	min = INT_MAX;
	if (!is_empty(values, SRC_TOP) && min > src->arr[src->top])
	{
		min = src->arr[src->top];
		location = SRC_TOP;
	}
	if (!is_empty(values, SRC_BOT) && min > src->arr[0])
	{
		min = src->arr[0];
		location = SRC_BOT;
	}
	if (!is_empty(values, DST_BOT) && min > dst->arr[0])
	{
		min = dst->arr[0];
		location = DST_BOT;
	}
	return (location);
}
