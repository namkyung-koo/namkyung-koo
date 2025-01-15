/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:40:23 by nakoo             #+#    #+#             */
/*   Updated: 2023/06/29 14:26:18 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*copy;
	size_t	src_len;
	size_t	i;

	if (n <= 0)
		return (NULL);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (copy == NULL)
		return (NULL);
	src_len = ft_strlen(src);
	i = 0;
	while (i < n)
	{
		if (src_len <= i)
			copy[i] = ' ';
		else if (src_len > i)
			copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
