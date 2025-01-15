/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 13:07:25 by nakoo             #+#    #+#             */
/*   Updated: 2023/06/27 21:41:51 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischr(char chr, char c)
{
	if (chr == c || chr == '\0')
		return (1);
	return (0);
}

static char	**ft_free_func(char	**str)
{
	size_t	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	*ft_strndup_s(char const *src, size_t n)
{
	size_t	i;
	char	*copy;

	if (n <= 0)
		return (0);
	copy = (char *)malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < n)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	**ft_slice_str(char	**split, char const *s, char c)
{
	size_t	i;
	size_t	first;
	size_t	cur;

	cur = 0;
	while (s[cur] != '\0' && ft_ischr(s[cur], c))
		cur++;
	first = cur;
	i = 0;
	while (s[cur] != '\0')
	{
		if (s[cur] && ft_ischr(s[cur], c) && !ft_ischr(s[cur + 1], c))
			first = cur + 1;
		else if (!(ft_ischr(s[cur], c)) && ft_ischr(s[cur + 1], c))
		{
			split[i] = ft_strndup_s(&s[first], cur - first + 1);
			if (split[i] == NULL)
				return (ft_free_func(split));
			i++;
		}
		cur++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	cnt;
	char	**split;

	if (s[0] == '\0')
		return ((char **)ft_calloc(1, sizeof(char *)));
	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (!ft_ischr(s[i], c) && ft_ischr(s[i + 1], c))
			cnt++;
		i++;
	}
	split = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!split)
		return (0);
	split[cnt] = 0;
	return (ft_slice_str(split, s, c));
}
