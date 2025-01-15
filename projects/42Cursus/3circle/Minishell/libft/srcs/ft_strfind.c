/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 13:53:15 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/22 08:52:59 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfind(char **str, char *find)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (str[i])
	{
		if (ft_strstr(str[i], find))
		{
			j = 0;
			while (str[i][j] != '=')
				j++;
			temp = ft_substr(str[i], 0, j);
			if (ft_strcmp(temp, find) == 0)
			{
				free(temp);
				return (str[i]);
			}
			free(temp);
		}
		i++;
	}
	return (NULL);
}
