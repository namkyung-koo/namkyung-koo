/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:31:40 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/31 14:19:49 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	make_triangle(t_stack *src, t_stack *dst, t_values *values, int nb)
{
	if (values->status != ZERO_TRIANGLE)
		return ;
	if (nb == 6)
		merge_below_six(src, dst);
	else if (nb == 5)
		merge_below_five(src, dst);
	else if (nb == 4)
		merge_below_four(src, dst);
	else if (nb == 3)
		merge_below_three(src, dst);
	else if (nb == 2)
		merge_below_two(src, dst);
	else
		push(src, dst);
}

void	make_rev_triangle(t_stack *src, t_stack *dst, t_values *values, int nb)
{
	if (values->status != ZERO_TRIANGLE)
		return ;
	if (nb == 6)
		rev_merge_below_six(src, dst);
	else if (nb == 5)
		rev_merge_below_five(src, dst);
	else if (nb == 4)
		rev_merge_below_four(src, dst);
	else if (nb == 3)
		rev_merge_below_three(src, dst);
	else if (nb == 2)
		rev_merge_below_two(src, dst);
	else
		push(src, dst);
}

void	handle_top(t_stack *src, t_stack *dst, int idx, int flag)
{
	if (idx == 2)
		rotate(src, dst, ONLY);
	if (idx == 1 || idx == 2)
		swap(src, dst, ONLY);
	push(src, dst);
	if (idx == 2)
	{
		reverse_rotate(src, dst, ONLY);
		if (flag == KEEP_NB)
			reverse_rotate(src, dst, ONLY);
	}
	if (flag == KEEP_NB && (idx == 0 || idx == 1))
		reverse_rotate(src, dst, ONLY);
}

void	handle_bottom(t_stack *src, t_stack *dst, int idx, int flag)
{
	int	nb;

	nb = idx + 1;
	while (nb > 0)
	{
		reverse_rotate(src, dst, ONLY);
		nb--;
	}
	push(src, dst);
	if (idx == 2)
	{
		rotate(src, dst, ONLY);
		rotate(src, dst, ONLY);
	}
	else if (idx == 1)
	{
		rotate(src, dst, ONLY);
		if (flag == KEEP_NB)
			rotate(src, dst, ONLY);
	}
	else if (idx == 0 && flag == KEEP_NB)
		rotate(src, dst, ONLY);
}

void	dup_args(t_stack *src, t_stack *dst, t_values *values, int depth)
{
	int	size;
	int	i;

	if (values->status == ZERO_TRIANGLE)
		return ;
	size = power(3, depth + 1);
	values->copy = (int *)malloc(sizeof(int) * size);
	if (!values->copy)
		return (free_and_null(&(src->arr)), free_and_null(&(dst->arr)), \
											free_and_null(&(values->args)));
	i = 0;
	while (i < size)
	{
		values->copy[i] = values->args[i];
		i++;
	}
	free_and_null(&(values)->args);
}
