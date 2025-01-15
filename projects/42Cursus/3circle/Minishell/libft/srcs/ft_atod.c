/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:29:27 by euiclee           #+#    #+#             */
/*   Updated: 2022/11/22 09:32:03 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	atod(char *str, double *result, double *tmp)
{
	while (*str && (*str == '.' || (*str >= '0' && *str <= '9')))
	{
		if (!*tmp)
		{
			*result = *result * 10 + (*str - '0');
			if (*(str + 1) == '.')
			{
				*tmp = 0.1;
				++str;
			}
		}
		else
		{
			*result += *tmp * (*str - '0');
			*tmp *= 0.1;
		}
		str++;
	}
}

double	ft_atod(char *str)
{
	double	tmp;
	double	sign;
	double	result;

	tmp = 0;
	sign = 1;
	result = 0;
	if (*str == '-')
	{
		sign *= -1;
		++str;
	}
	atod(str, &result, &tmp);
	return (result * sign);
}
