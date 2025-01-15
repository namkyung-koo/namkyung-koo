/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:47:47 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/27 08:53:33 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	env_qut_check(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'' && *str != '\0')
			{
				if (*str == '$')
					return (FALSE);
				str++;
			}
		}
		else if (*str == '\"')
		{
			str++;
			while (*str != '\"' && *str != '\0')
				str++;
		}
		str++;
	}
	return (TRUE);
}

int	check_quote_num(char *str)
{
	int	is_qut;
	int	is_db;
	int	rm_qut;
	int	i;

	i = 0;
	is_db = 0;
	is_qut = 0;
	rm_qut = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			is_qut++;
		else if (str[i] == '\"')
			is_db++;
		if ((str[i] == '\'' && is_qut != 0 \
		&& is_qut % 2 == 0 && is_db % 2 == 0) \
		|| (str[i] == '\"' && is_db != 0 \
		&& is_db % 2 == 0 && is_qut % 2 == 0))
			rm_qut += 2;
		i++;
	}
	return (rm_qut);
}

char	*rm_quote(char *str, int len)
{
	t_quo	q;

	q.temp = str;
	q.ret = ft_calloc(len + 1, sizeof(char));
	q.i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str != '\'' && *str != '\"')
			q.ret[q.i++] = *str++;
		if (*str == '\'')
			q.loca = ft_strchr(++str, '\'');
		else if (*str == '\"')
			q.loca = ft_strchr(++str, '\"');
		if (*str != '\0' && q.loca && *str != *q.loca)
		{
			while (str && q.loca && *str != *q.loca)
				q.ret[q.i++] = *str++;
			str++;
		}
		else if (*str != '\0')
			str++;
	}
	return (free(q.temp), q.ret);
}

void	check_quote(t_tokens *tokens)
{
	int	i;
	int	len;
	int	ret_len;

	i = 0;
	while (tokens->token[i])
	{
		len = check_quote_num(tokens->token[i]);
		ret_len = ft_strlen(tokens->token[i]) - len;
		if (len)
			tokens->token[i] = rm_quote(tokens->token[i], ret_len);
		i++;
	}
}
