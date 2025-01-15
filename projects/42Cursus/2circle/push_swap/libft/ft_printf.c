/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:53:25 by nakoo             #+#    #+#             */
/*   Updated: 2022/09/12 15:45:03 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	int			printed;

	va_start(args, fmt);
	printed = 0;
	while (*fmt != '\0')
	{
		if (*fmt != '%')
			printed += write (1, fmt, 1);
		else if (*fmt == '%')
		{
			fmt++;
			printed += ft_vprintf(&fmt, &args);
		}
		fmt++;
	}
	va_end(args);
	return (printed);
}

int	ft_vprintf(const char **fmt, va_list *args)
{
	int		flags;
	int		printed;
	t_opt	opt;

	flags = 0;
	flags = set_flags(fmt);
	opt = set_options(fmt, &flags);
	printed = set_specifier(fmt, args, &flags, &opt);
	return (printed);
}

int	set_flags(const char **fmt)
{
	int	flags;

	flags = 0;
	while (ft_strchr("-+# 0", **fmt))
	{
		if (**fmt == '-')
			flags |= LEFT;
		else if (**fmt == '+')
			flags |= PLUS;
		else if (**fmt == '#')
			flags |= SPECIAL;
		else if (**fmt == ' ')
			flags |= SPACE;
		else if (**fmt == '0')
			flags |= ZEROPAD;
		(*fmt)++;
	}
	return (flags);
}

t_opt	set_options(const char **fmt, int *flags)
{
	t_opt	opt;

	opt.width = 0;
	if (ft_isdigit(**fmt))
		opt.width = ft_skip_atoi(fmt);
	opt.precision = -1;
	if (**fmt == '.')
	{
		(*fmt)++;
		opt.precision = ft_skip_atoi(fmt);
		if (opt.precision == 0)
			*flags |= ZERO;
	}
	return (opt);
}

int	set_specifier(const char **fmt, va_list *args, int *flags, t_opt *opt)
{
	int	printed;

	printed = 0;
	if (opt->precision != -1 && *flags & ZEROPAD)
		*flags &= ~ZEROPAD;
	if (**fmt == '%')
		ft_printf_percent(flags, opt, &printed);
	else if (**fmt == 'c')
		ft_printf_c(flags, opt, &printed, va_arg(*args, int));
	else if (**fmt == 's')
		ft_printf_s(flags, opt, &printed, va_arg(*args, char *));
	else if (**fmt == 'd' || **fmt == 'i')
		ft_printf_di(flags, opt, &printed, va_arg(*args, int));
	else if (**fmt == 'u')
		ft_printf_u(flags, opt, &printed, va_arg(*args, unsigned int));
	else if (**fmt == 'x' || **fmt == 'X')
	{
		if (**fmt == 'x')
			*flags |= SMALL;
		ft_printf_x(flags, opt, &printed, va_arg(*args, unsigned int));
	}
	else if (**fmt == 'p')
		ft_printf_p(flags, opt, &printed, va_arg(*args, unsigned long long));
	return (printed);
}
