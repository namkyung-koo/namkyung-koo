/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifier2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 03:31:24 by nakoo             #+#    #+#             */
/*   Updated: 2022/09/12 15:44:42 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_x(int *flags, t_opt *opt, int *printed, unsigned int n)
{
	int	len;
	int	padlen;

	*flags |= HEX;
	len = get_len(n, flags);
	padlen = get_padlen(n, flags, opt, len);
	if (*flags & SPECIAL && n != 0)
		opt->width -= 2;
	if (!(*flags & LEFT) && opt->width > opt->precision && !(*flags & ZEROPAD))
		*printed += put_padding(' ', opt->width - padlen);
	if (*flags & SPECIAL && n != 0)
	{
		if (*flags & SMALL)
			*printed += write(1, "0x", 2);
		else if (!(*flags & SMALL))
			*printed += write(1, "0X", 2);
	}
	if (*flags & ZEROPAD && opt->width > len)
		*printed += put_padding('0', opt->width - len);
	else if (opt->precision > len)
		*printed += put_padding('0', opt->precision - len);
	if (!(*flags & ZERO && n == 0))
		print_hexadecimal(n, printed, flags);
	if (*flags & LEFT && opt->width > opt->precision)
		*printed += put_padding(' ', opt->width - padlen);
}

void	ft_printf_p(int *flags, t_opt *opt, int *printed, unsigned long long n)
{
	int	len;

	len = get_address_len(n);
	if (n == 0)
		len = 1;
	if (!(*flags & SMALL))
		*flags |= SMALL;
	if (!(*flags & LEFT) && opt->width > len + 2)
		*printed += put_padding(' ', opt->width - len - 2);
	*printed += write(1, "0x", 2);
	print_hexadecimal(n, printed, flags);
	if (*flags & LEFT && opt->width > len + 2)
		*printed += put_padding(' ', opt->width - len - 2);
}
