/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:49:21 by nakoo             #+#    #+#             */
/*   Updated: 2022/09/12 15:44:37 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_percent(int *flags, t_opt *opt, int *printed)
{
	if (opt->width > 1 && *flags & ZEROPAD && !(*flags & LEFT))
		*printed += put_padding('0', opt->width - 1);
	else if (opt->width > 1 && !(*flags & LEFT))
		*printed += put_padding(' ', opt->width - 1);
	*printed += write(1, "%", 1);
	if (opt->width > 1 && *flags & LEFT)
		*printed += put_padding(' ', opt->width - 1);
}

void	ft_printf_c(int *flags, t_opt *opt, int *printed, int c)
{
	if (opt->width > 1 && !(*flags & LEFT))
		*printed += put_padding(' ', opt->width - 1);
	*printed += write(1, &c, 1);
	if (opt->width > 1 && *flags & LEFT)
		*printed += put_padding(' ', opt->width - 1);
}

void	ft_printf_s(int *flags, t_opt *opt, int *printed, char *str)
{
	int	str_len;

	if (str == 0)
		str = "(null)";
	str_len = ft_strlen(str);
	if (opt->precision < str_len && opt->precision != -1)
		str_len = opt->precision;
	if (opt->width > str_len && !(*flags & LEFT))
		*printed += put_padding(' ', opt->width - str_len);
	*printed += write(1, str, str_len);
	if (opt->width > str_len && *flags & LEFT)
		*printed += put_padding(' ', opt->width - str_len);
}

void	ft_printf_di(int *flags, t_opt *opt, int *printed, int n)
{
	int			len;
	int			padlen;
	char		sign;
	long long	num;

	num = convert_longlong(n, flags);
	len = get_len(num, flags);
	sign = get_sign(flags, opt);
	padlen = get_padlen(num, flags, opt, len);
	if (sign != '\0')
		opt->width -= 1;
	if (!(*flags & LEFT) && opt->width > opt->precision && !(*flags & ZEROPAD))
		*printed += put_padding(' ', opt->width - padlen);
	if (sign != '\0')
		*printed += write(1, &sign, 1);
	if (*flags & ZEROPAD && opt->width > len)
		*printed += put_padding('0', opt->width - len);
	else if (opt->precision > len)
		*printed += put_padding('0', opt->precision - len);
	if (!(*flags & ZERO && num == 0))
		print_decimal(num, printed);
	if (*flags & LEFT && opt->width > opt->precision)
		*printed += put_padding(' ', opt->width - padlen);
}

void	ft_printf_u(int *flags, t_opt *opt, int *printed, unsigned int n)
{
	int	len;
	int	padlen;

	len = get_len(n, flags);
	padlen = get_padlen(n, flags, opt, len);
	if (!(*flags & LEFT) && opt->width > opt->precision && !(*flags & ZEROPAD))
		*printed += put_padding(' ', opt->width - padlen);
	if (*flags & ZEROPAD && opt->width > len)
		*printed += put_padding('0', opt->width - len);
	else if (opt->precision > len)
		*printed += put_padding('0', opt->precision - len);
	if (!(*flags & ZERO && n == 0))
		print_decimal(n, printed);
	if (*flags & LEFT && opt->width > opt->precision)
		*printed += put_padding(' ', opt->width - padlen);
}
