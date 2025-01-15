/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:54:25 by nakoo             #+#    #+#             */
/*   Updated: 2022/09/12 17:26:11 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# define ZEROPAD 1	/* pad with zero */
# define PLUS 2		/* show plus */
# define SPACE 4	/* space if plus */
# define LEFT 8		/* left justified */
# define SMALL 16	/* 0x20 */
# define SPECIAL 32	/* 0x */
# define HEX 64		/* convert to hexadecimal */
# define MINUS 128	/* negative number */
# define ZERO 256	/* if precision is zero or . */

# define HEX_LOW "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"

typedef struct s_options
{
	int	width;
	int	precision;
}	t_opt;

/* ft_printf.c */
int			ft_printf(const char *fmt, ...);
int			ft_vprintf(const char **fmt, va_list *args);
int			set_flags(const char **fmt);
t_opt		set_options(const char **fmt, int *flags);
int			set_specifier(const char **fmt, va_list *args, int *flags, \
																t_opt *opt);

/* ft_printf_specifier.c */
void		ft_printf_percent(int *flags, t_opt *opt, int *printed);
void		ft_printf_c(int *flags, t_opt *opt, int *printed, int c);
void		ft_printf_s(int *flags, t_opt *opt, int *printed, char *str);
void		ft_printf_di(int *flags, t_opt *opt, int *printed, int n);
void		ft_printf_u(int *flags, t_opt *opt, int *printed, unsigned int n);

/* ft_printf_specifier2.c */
void		ft_printf_x(int *flags, t_opt *opt, int *printed, unsigned int n);
void		ft_printf_p(int *flags, t_opt *opt, int *pritned, \
														unsigned long long n);

/* ft_printf_utils.c */
int			get_len(long long n, int *flags);
int			get_address_len(unsigned long long n);
int			put_padding(char c, int len);
char		get_sign(int *flags, t_opt *opt);
int			ft_skip_atoi(const char **fmt);
/* ft_printf_utils2.c */
void		print_decimal(long long n, int *printed);
void		print_hexadecimal(unsigned long long n, int *printed, int *flags);
int			get_padlen(unsigned long long n, int *flags, t_opt *opt, int len);
long long	convert_longlong(int n, int *flags);

/* ft_printf_utils3.c */
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);

#endif