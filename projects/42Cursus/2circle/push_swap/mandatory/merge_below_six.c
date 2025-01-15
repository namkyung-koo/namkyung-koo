/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_below_six.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:09:11 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/29 17:00:51 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_below_six(t_stack *src, t_stack *dst)
{
	int	max;

	max = find_merge_max(src, src->top - 2, 5);
	if (max == src->arr[src->top] || max == src->arr[src->top - 1] \
										|| max == src->arr[src->top - 2])
	{
		if (max == src->arr[src->top - 2])
			handle_top(src, dst, 2, KEEP_NB);
		else if (max == src->arr[src->top - 1])
			handle_top(src, dst, 1, KEEP_NB);
		else
			handle_top(src, dst, 0, KEEP_NB);
	}
	else if (max == src->arr[0] || max == src->arr[1] || max == src->arr[2])
	{
		if (max == src->arr[2])
			handle_bottom(src, dst, 2, NOTHING);
		else if (max == src->arr[1])
			handle_bottom(src, dst, 1, NOTHING);
		else
			handle_bottom(src, dst, 0, NOTHING);
	}
	merge_below_five(src, dst);
}

void	merge_below_five(t_stack *src, t_stack *dst)
{
	int	max;

	max = find_merge_max(src, src->top - 2, 4);
	if (max == src->arr[src->top] || max == src->arr[src->top - 1] \
										|| max == src->arr[src->top - 2])
	{
		if (max == src->arr[src->top - 2])
			handle_top(src, dst, 2, NOTHING);
		else if (max == src->arr[src->top - 1])
			handle_top(src, dst, 1, NOTHING);
		else
			handle_top(src, dst, 0, NOTHING);
	}
	else if (max == src->arr[0] || max == src->arr[1])
	{
		if (max == src->arr[1])
			handle_bottom(src, dst, 1, KEEP_NB);
		else
			handle_bottom(src, dst, 0, KEEP_NB);
	}
	merge_below_four(src, dst);
}

void	merge_below_four(t_stack *src, t_stack *dst)
{
	int	max;

	max = find_merge_max(src, src->top - 1, 3);
	if (max == src->arr[src->top] || max == src->arr[src->top - 1])
	{
		if (max == src->arr[src->top - 1])
			handle_top(src, dst, 1, KEEP_NB);
		else
			handle_top(src, dst, 0, KEEP_NB);
	}
	else if (max == src->arr[0] || max == src->arr[1])
	{
		if (max == src->arr[1])
			handle_bottom(src, dst, 1, NOTHING);
		else
			handle_bottom(src, dst, 0, NOTHING);
	}
	merge_below_three(src, dst);
}

void	merge_below_three(t_stack *src, t_stack *dst)
{
	int	max;

	max = find_merge_max(src, src->top - 1, 2);
	if (max == src->arr[src->top] || max == src->arr[src->top - 1])
	{
		if (max == src->arr[src->top - 1])
			handle_top(src, dst, 1, KEEP_NB);
		else
			handle_top(src, dst, 0, KEEP_NB);
	}
	else if (max == src->arr[0])
		handle_bottom(src, dst, 0, NOTHING);
	merge_below_two(src, dst);
}

void	merge_below_two(t_stack *src, t_stack *dst)
{
	if (src->arr[src->top] < src->arr[src->top - 1])
		swap(src, dst, ONLY);
	push(src, dst);
	push(src, dst);
}
