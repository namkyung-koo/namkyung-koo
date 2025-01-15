/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:54:53 by euiclee           #+#    #+#             */
/*   Updated: 2022/11/22 09:29:16 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			s_len;
	unsigned char	*s_tmp;

	s_len = ft_strlen(s);
	s_tmp = (unsigned char *)s;
	while (s_len != 0 && s_tmp[s_len] != (unsigned char)c)
		s_len--;
	if (s_tmp[s_len] == (unsigned char)c)
		return ((char *)(s_tmp + (unsigned char)s_len));
	return (0);
}
