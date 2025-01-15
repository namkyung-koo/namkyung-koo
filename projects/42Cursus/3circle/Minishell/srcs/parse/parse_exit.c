/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:33:46 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/20 13:51:38 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*re_quo(char **loca, char *origin)
{
	char	*temp;
	char	*ret;
	int		exit_len;
	int		len;

	temp = ft_itoa(g_exit);
	exit_len = ft_strlen(temp);
	len = 0;
	while (origin[len])
		len++;
	ret = ft_calloc(exit_len + len - 1, sizeof(char));
	ft_memmove(ret, origin, get_len(origin, 0));
	ft_memmove(ret + get_len(origin, 0), temp, exit_len);
	len = get_len(ret, 2);
	ft_memmove(ret + len, ++(*loca), ft_strlen((*loca)));
	*loca = ret + len;
	free(temp);
	free(origin);
	return (ret);
}
