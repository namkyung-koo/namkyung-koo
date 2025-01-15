/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 19:29:16 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/28 00:11:11 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_depth(int nb)
{
	int	depth;
	int	min_size;

	min_size = 5;
	depth = 0;
	while (nb > min_size)
	{
		min_size *= 3;
		depth++;
	}
	return (depth);
}

int	get_order(int idx)
{
	int	flip;
	int	range;
	int	mirror;
	int	dist;

	flip = 0;
	while (idx > 0)
	{
		range = 0;
		while (idx / power(3, range))
			range++;
		mirror = power(3, range - 1);
		dist = idx - mirror;
		dist %= mirror;
		idx = mirror - dist - 1;
		flip++;
	}
	return (flip);
}

int	power(int base, int exp)
{
	int	res;
	int	i;

	res = 1;
	i = 0;
	while (i < exp)
	{
		res *= base;
		i++;
	}
	return (res);
}

void	ret_one_third(t_values *values, int triangle)
{
	int	idx;
	int	i;

	values->one_third = 0;
	idx = triangle - 1;
	i = triangle / 3;
	while (i > 0)
	{
		values->one_third += values->args[idx];
		idx--;
		i--;
	}
}

int	is_empty(t_values *values, int idx)
{
	if (values->tmp[idx] == 0)
		return (1);
	return (0);
}
