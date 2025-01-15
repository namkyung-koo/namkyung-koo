/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:43:40 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/31 16:02:44 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_operation(t_stack *a, t_stack *b)
{
	t_values	values;

	ft_memset(&values, 0, sizeof(t_values));
	b->arr = (int *)malloc(sizeof(int) * (a->top + 1));
	if (!b->arr)
		free_and_null(&(a->arr));
	b->top = -1;
	if ((a->top) + 1 <= 5)
		sort_below_five(a, b);
	else
		merge_sort(&a, &b, &values);
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
	ft_printf("p%c\n", dst->name);
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
		ft_printf("s%c\n", src->name);
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
		ft_printf("ss\n");
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
	if (flag == ONLY)
		ft_printf("r%c\n", src->name);
	else if (flag == BOTH)
		rotate(dst, src, flag - 1);
	if (flag == 1)
		ft_printf("rr\n");
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
	if (flag == ONLY)
		ft_printf("rr%c\n", src->name);
	else if (flag == BOTH)
		reverse_rotate(dst, src, flag - 1);
	if (flag == 1)
		ft_printf("rrr\n");
}
