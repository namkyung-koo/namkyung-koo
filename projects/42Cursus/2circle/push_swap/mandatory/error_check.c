/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:46:39 by nakoo             #+#    #+#             */
/*   Updated: 2022/10/28 10:17:53 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_and_null(int **ptr)
{
	if (*ptr != NULL)
		free(*ptr);
	*ptr = NULL;
}

void	error_and_exit(int *arr, int flag)
{
	free_and_null(&arr);
	if (flag == ERROR)
		write(2, "Error\n", 6);
	exit(0);
}

void	detect_duplicates(t_stack *a)
{
	int	i;
	int	j;

	i = 0;
	while (i < a->top)
	{
		j = i + 1;
		while (j <= a->top)
		{
			if (a->arr[i] == a->arr[j])
				error_and_exit(a->arr, ERROR);
			j++;
		}
		i++;
	}
}

void	check_sort(t_stack *a)
{
	int	flag;
	int	comp;
	int	i;

	comp = a->arr[0];
	flag = SORTED;
	i = 1;
	while (i <= a->top)
	{
		if (comp > a->arr[i])
			comp = a->arr[i];
		else
		{
			flag = NOT_SORTED;
			break ;
		}
		i++;
	}
	if (flag == SORTED)
		error_and_exit(a->arr, NOTHING);
}
