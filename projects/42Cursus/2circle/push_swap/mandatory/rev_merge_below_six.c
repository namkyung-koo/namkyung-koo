/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_merge_below_six.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:11:38 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/29 17:02:14 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_merge_below_six(t_stack *src, t_stack *dst)
{
	int	min;

	min = find_merge_min(src, src->top - 2, 5);
	if (min == src->arr[src->top] || min == src->arr[src->top - 1] \
										|| min == src->arr[src->top - 2])
	{
		if (min == src->arr[src->top - 2])
			handle_top(src, dst, 2, KEEP_NB);
		else if (min == src->arr[src->top - 1])
			handle_top(src, dst, 1, KEEP_NB);
		else
			handle_top(src, dst, 0, KEEP_NB);
	}
	else if (min == src->arr[0] || min == src->arr[1] || min == src->arr[2])
	{
		if (min == src->arr[2])
			handle_bottom(src, dst, 2, NOTHING);
		else if (min == src->arr[1])
			handle_bottom(src, dst, 1, NOTHING);
		else
			handle_bottom(src, dst, 0, NOTHING);
	}
	rev_merge_below_five(src, dst);
}

void	rev_merge_below_five(t_stack *src, t_stack *dst)
{
	int	min;

	min = find_merge_min(src, src->top - 2, 4);
	if (min == src->arr[src->top] || min == src->arr[src->top - 1] \
										|| min == src->arr[src->top - 2])
	{
		if (min == src->arr[src->top - 2])
			handle_top(src, dst, 2, NOTHING);
		else if (min == src->arr[src->top - 1])
			handle_top(src, dst, 1, NOTHING);
		else
			handle_top(src, dst, 0, NOTHING);
	}
	else if (min == src->arr[0] || min == src->arr[1])
	{
		if (min == src->arr[1])
			handle_bottom(src, dst, 1, KEEP_NB);
		else
			handle_bottom(src, dst, 0, KEEP_NB);
	}
	rev_merge_below_four(src, dst);
}

void	rev_merge_below_four(t_stack *src, t_stack *dst)
{
	int	min;

	min = find_merge_min(src, src->top - 1, 3);
	if (min == src->arr[src->top] || min == src->arr[src->top - 1])
	{
		if (min == src->arr[src->top - 1])
			handle_top(src, dst, 1, KEEP_NB);
		else
			handle_top(src, dst, 0, KEEP_NB);
	}
	else if (min == src->arr[0] || min == src->arr[1])
	{
		if (min == src->arr[1])
			handle_bottom(src, dst, 1, NOTHING);
		else
			handle_bottom(src, dst, 0, NOTHING);
	}
	rev_merge_below_three(src, dst);
}

void	rev_merge_below_three(t_stack *src, t_stack *dst)
{
	int	min;

	min = find_merge_min(src, src->top - 1, 2);
	if (min == src->arr[src->top] || min == src->arr[src->top - 1])
	{
		if (min == src->arr[src->top - 1])
			handle_top(src, dst, 1, KEEP_NB);
		else
			handle_top(src, dst, 0, KEEP_NB);
	}
	else if (min == src->arr[0])
		handle_bottom(src, dst, 0, NOTHING);
	rev_merge_below_two(src, dst);
}

void	rev_merge_below_two(t_stack *src, t_stack *dst)
{
	if (src->arr[src->top] > src->arr[src->top - 1])
		swap(src, dst, ONLY);
	push(src, dst);
	push(src, dst);
}
