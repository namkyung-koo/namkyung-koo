/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:46:14 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/01 18:41:07 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_b_to_a(t_stack *src, t_stack *dst, t_values *values)
{
	free_and_null(&(values)->args);
	while (values->status % 2 && dst->top > -1)
	{
		reverse_rotate(dst, src, ONLY);
		push(dst, src);
	}
}

long long	ft_atoll(t_stack *a, const char *str)
{
	long long	res;
	int			sign;

	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (*str == '\0')
		error_and_exit(a->arr, ERROR);
	res = 0;
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (*str != '\0')
		error_and_exit(a->arr, ERROR);
	return (res * sign);
}

int	parse_argv(t_stack *a, char *argv)
{
	long long	nb;

	nb = ft_atoll(a, argv);
	if (nb < INT_MIN || nb > INT_MAX)
		error_and_exit(a->arr, ERROR);
	return (nb);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	int		nb;
	int		i;

	if (argc < 2)
		return (0);
	a.arr = (int *)malloc(sizeof(int) * (argc - 1));
	if (!a.arr)
		return (0);
	a.top = argc - 2;
	a.name = 'a';
	b.name = 'b';
	i = 0;
	while (argc - 1 > 0)
	{
		nb = parse_argv(&a, argv[argc - 1]);
		a.arr[i] = nb;
		i++;
		argc--;
	}
	detect_duplicates(&a);
	check_sort(&a);
	do_operation(&a, &b);
	return (0);
}
