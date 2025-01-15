/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 11:17:46 by nakoo             #+#    #+#             */
/*   Updated: 2022/07/18 19:15:46 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	size_t			i;
	size_t			s_len;
	size_t			t_start;

	t_start = (size_t)start;
	s_len = ft_strlen(s);
	if (s_len <= t_start)
		return (ft_strdup(""));
	if (s_len < len)
		len = s_len - t_start;
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = s[t_start];
		i++;
		t_start++;
	}
	tmp[i] = '\0';
	return (tmp);
}
