/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_below_five.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:49:07 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/28 11:08:52 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_below_five(t_stack *a, t_stack *b)
{
	int	min;

	if ((a->top) + 1 == 5)
	{
		min = find_min(a);
		if (min == a->arr[0] || min == a->arr[1])
		{
			if (min == a->arr[1])
				reverse_rotate(a, b, ONLY);
			reverse_rotate(a, b, ONLY);
		}
		else if (min == a->arr[2] || min == a->arr[3])
		{
			if (min == a->arr[2])
				rotate(a, b, ONLY);
			rotate(a, b, ONLY);
		}
		push(a, b);
	}
	sort_below_four(a, b);
}

void	sort_below_four(t_stack *a, t_stack *b)
{
	int	min;

	if ((a->top) + 1 == 4)
	{
		min = find_min(a);
		if (min == a->arr[0] || min == a->arr[1])
		{
			if (min == a->arr[1])
				reverse_rotate(a, b, ONLY);
			reverse_rotate(a, b, ONLY);
		}
		else if (min == a->arr[2])
			rotate(a, b, ONLY);
		push(a, b);
	}
	sort_below_three(a, b);
}

void	sort_below_three(t_stack *a, t_stack *b)
{
	int	min;

	if ((a->top) + 1 == 3)
	{
		min = find_min(a);
		if (min == a->arr[2] && a->arr[1] > a->arr[0])
		{
			reverse_rotate(a, b, ONLY);
			swap(a, b, ONLY);
		}
		else if (min == a->arr[1] && a->arr[0] > a->arr[2])
			swap(a, b, ONLY);
		else if (min == a->arr[1] && a->arr[0] < a->arr[2])
			rotate(a, b, ONLY);
		else if (min == a->arr[0] && a->arr[2] > a->arr[1])
		{
			swap(a, b, ONLY);
			reverse_rotate(a, b, ONLY);
		}
		else if (min == a->arr[0] && a->arr[2] < a->arr[1])
			reverse_rotate(a, b, ONLY);
	}
	while (b->top > -1)
		push(b, a);
	sort_below_two(a, b);
}

void	sort_below_two(t_stack *a, t_stack *b)
{
	if ((a->top) + 1 == 2)
	{
		if (a->arr[a->top] > a->arr[0])
			swap(a, b, ONLY);
	}
}

int	find_min(t_stack *a)
{
	int	min;
	int	i;

	min = a->arr[0];
	i = 1;
	while (i <= a->top)
	{
		if (min > a->arr[i])
			min = a->arr[i];
		i++;
	}
	return (min);
}
