/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:28:30 by euiclee           #+#    #+#             */
/*   Updated: 2022/11/22 09:30:25 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cnt_word(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			cnt++;
		s++;
	}
	return (cnt);
}

static size_t	ft_len_word(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*ft_strndup(char const *s, size_t len)
{
	char	*word;
	char	*temp;

	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (0);
	temp = word;
	while (len--)
		*temp++ = *s++;
	return (word);
}

static char	**ft_free(char **s, size_t i)
{
	while (i--)
		free(s[i]);
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	size_t	i;
	char	**result;

	if (!s)
		return (0);
	word = ft_cnt_word(s, c);
	result = (char **)ft_calloc(word + 1, sizeof(char *));
	if (!result)
		return (0);
	i = 0;
	while (i < word)
	{
		while (*s == c)
			s++;
		result[i] = ft_strndup(s, ft_len_word(s, c));
		if (!result[i])
			return (ft_free(result, i));
		s += ft_len_word(s, c);
		i++;
	}
	return (result);
}
