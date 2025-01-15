/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:58:19 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/20 14:17:31 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_assert(int expression, char *msg, int error_code)
{
	if (expression == FALSE)
	{
		perror(msg);
		exit(error_code);
	}
}
