/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:45:51 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/02 08:18:50 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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

void	do_instructions(t_stack *a, t_stack *b, char *op)
{
	if (ft_strncmp(op, "pb\n", 3) == 0)
		push(a, b);
	else if (ft_strncmp(op, "pa\n", 3) == 0)
		push(b, a);
	else if (ft_strncmp(op, "sa\n", 3) == 0)
		swap(a, b, ONLY);
	else if (ft_strncmp(op, "sb\n", 3) == 0)
		swap(b, a, ONLY);
	else if (ft_strncmp(op, "ss\n", 3) == 0)
		swap(a, b, BOTH);
	else if (ft_strncmp(op, "ra\n", 3) == 0)
		rotate(a, b, ONLY);
	else if (ft_strncmp(op, "rb\n", 3) == 0)
		rotate(b, a, ONLY);
	else if (ft_strncmp(op, "rr\n", 3) == 0)
		rotate(a, b, BOTH);
	else if (ft_strncmp(op, "rra\n", 4) == 0)
		reverse_rotate(a, b, ONLY);
	else if (ft_strncmp(op, "rrb\n", 4) == 0)
		reverse_rotate(b, a, ONLY);
	else if (ft_strncmp(op, "rrr\n", 4) == 0)
		reverse_rotate(a, b, BOTH);
	else
		return (free_and_null(&(a->arr)), error_and_exit(b->arr, ERROR));
}

void	parse_instructions(t_stack *a, t_stack *b)
{
	char	*op;
	int		flag;

	flag = 1;
	while (1)
	{
		op = get_next_line(0);
		if (op == NULL)
			break ;
		do_instructions(a, b, op);
		free(op);
		op = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
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
		a.arr[i] = parse_argv(&a, argv[argc - 1]);
		i++;
		argc--;
	}
	detect_duplicates(&a);
	do_operation(&a, &b);
	return (0);
}
