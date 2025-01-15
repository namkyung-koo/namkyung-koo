/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:33:55 by nakoo             #+#    #+#             */
/*   Updated: 2022/09/14 11:31:23 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_len(long long n, int *flags)
{
	int	len;
	int	base;

	if (n == 0)
		return (1);
	base = 10;
	if (*flags & HEX)
		base = 16;
	len = 0;
	while (n > 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

int	get_address_len(unsigned long long n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	put_padding(char c, int len)
{
	int	i;

	i = 0;
	if (len < 0)
		return (0);
	while (i < len)
	{
		write (1, &c, 1);
		i++;
	}
	return (len);
}

char	get_sign(int *flags, t_opt *opt)
{
	char	sign;

	sign = '\0';
	if (*flags & MINUS)
		sign = '-';
	if (!(*flags & MINUS) && *flags & PLUS)
		sign = '+';
	else if (!(*flags & MINUS) && !(*flags & PLUS) && *flags & SPACE)
		sign = ' ';
	if (opt->precision == -1)
		opt->precision = 0;
	return (sign);
}

int	ft_skip_atoi(const char **fmt)
{
	int	i;

	i = 0;
	while (ft_isdigit(**fmt))
	{
		i = i * 10 + (**fmt - '0');
		(*fmt)++;
	}
	return (i);
}
