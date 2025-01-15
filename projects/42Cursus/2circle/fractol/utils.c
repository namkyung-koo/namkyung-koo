/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:09:27 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/15 10:08:35 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	space_and_sign(const char **str, double *res)
{
	int	sign;

	sign = 0;
	*res = 0;
	while ((9 <= **str && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = 1;
		(*str)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	double	decimal;
	double	res;
	int		sign;
	int		dec;

	decimal = 1;
	dec = 0;
	sign = space_and_sign(&str, &res);
	while (*str != '\0')
	{
		if ('0' <= *str && *str <= '9')
		{
			res = res * 10 + (*str - '0');
			if (dec == 1)
				decimal *= 10;
		}
		else if (*str == '.')
			dec = 1;
		else
			break ;
		str++;
	}
	if (sign == 1)
		return (-(res / decimal));
	return (res / decimal);
}
