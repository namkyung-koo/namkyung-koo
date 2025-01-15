/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:19:14 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/23 18:43:57 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	swap(int *a, int *b)
{
	if (a == b)
		return ;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int	error_msg(int expression, char *msg)
{
	if (expression == FALSE)
	{
		perror(msg);
		g_exit = 1;
		return (FALSE);
	}
	return (TRUE);
}
