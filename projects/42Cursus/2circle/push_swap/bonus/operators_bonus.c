/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:43:40 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/01 15:52:44 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	do_operation(t_stack *a, t_stack *b)
{
	b->arr = (int *)malloc(sizeof(int) * (a->top + 1));
	if (!b->arr)
		free_and_null(&(a->arr));
	b->top = -1;
	parse_instructions(a, b);
	check_sort_and_print(a, b);
	free_and_null(&(a->arr));
	free_and_null(&(b->arr));
}

void	push(t_stack *src, t_stack *dst)
{
	int	data;

	if (src->top == -1)
		return ;
	data = src->arr[src->top];
	(src->top)--;
	(dst->top)++;
	dst->arr[dst->top] = data;
}

void	swap(t_stack *src, t_stack *dst, int flag)
{
	int	tmp;

	if (flag == ONLY)
	{
		if ((src->top) + 1 < 2)
			return ;
		tmp = src->arr[src->top];
		src->arr[src->top] = src->arr[src->top - 1];
		src->arr[src->top - 1] = tmp;
	}
	else
	{
		if ((src->top + 1) < 2 || (dst->top + 1) < 2)
			return ;
		tmp = src->arr[src->top];
		src->arr[src->top] = src->arr[src->top - 1];
		src->arr[src->top - 1] = tmp;
		tmp = dst->arr[src->top];
		dst->arr[src->top] = dst->arr[src->top - 1];
		dst->arr[src->top - 1] = tmp;
	}
}

void	rotate(t_stack *src, t_stack *dst, int flag)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = src->arr[src->top];
	while (i < src->top)
	{
		src->arr[src->top - i] = src->arr[src->top - 1 - i];
		i++;
	}
	src->arr[0] = tmp;
	if (flag == BOTH)
		rotate(dst, src, flag - 1);
	if (flag == 1)
		return ;
}

void	reverse_rotate(t_stack *src, t_stack *dst, int flag)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = src->arr[0];
	while (i < src->top)
	{
		src->arr[i] = src->arr[i + 1];
		i++;
	}
	src->arr[src->top] = tmp;
	if (flag == BOTH)
		reverse_rotate(dst, src, flag - 1);
	if (flag == 1)
		return ;
}
