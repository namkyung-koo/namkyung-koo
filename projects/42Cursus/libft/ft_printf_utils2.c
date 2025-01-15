/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:53:17 by nakoo             #+#    #+#             */
/*   Updated: 2022/09/12 15:44:53 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_decimal(long long n, int *printed)
{
	char	c;

	if (n >= 10)
		print_decimal(n / 10, printed);
	c = (n % 10) + '0';
	*printed += write(1, &c, 1);
}

void	print_hexadecimal(unsigned long long n, int *printed, int *flags)
{
	char	*base;

	base = HEX_LOW;
	if (!(*flags & SMALL))
		base = HEX_UP;
	if (n >= 16)
		print_hexadecimal(n / 16, printed, flags);
	*printed += write(1, &base[n % 16], 1);
}

int	get_padlen(unsigned long long n, int *flags, t_opt *opt, int len)
{
	int	padlen;

	if (*flags & ZERO && n == 0)
		return (0);
	padlen = 0;
	if (opt->precision == -1)
		opt->precision = 0;
	if (opt->precision > len)
		padlen = opt->precision;
	else if (opt->precision <= len)
		padlen = len;
	return (padlen);
}

long long	convert_longlong(int n, int *flags)
{
	long long	num;

	num = (long long)n;
	if (num < 0)
	{
		num *= -1;
		*flags |= MINUS;
	}
	return (num);
}
