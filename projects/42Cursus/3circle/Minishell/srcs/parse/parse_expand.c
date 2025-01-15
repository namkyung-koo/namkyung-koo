/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:50:40 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/22 09:50:24 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_space(char *str)
{
	int	i;
	int	qut;
	int	space;

	i = 0;
	qut = 0;
	space = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			qut = 1;
		if (str[i] == ' ')
			space = 1;
		i++;
	}
	if (qut == 0 && space == 1)
		return (TRUE);
	else
		return (FALSE);
}

int	cnt_tok(char **tok)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (tok[i])
	{
		j = 0;
		if (check_space(tok[i]))
		{
			while (tok[i][j])
			{
				if (tok[i][j] != ' '
					&& (tok[i][j + 1] == ' ' || tok[i][j] == '\0'))
					num++;
				j++;
			}
		}
		i++;
		num++;
	}
	return (num);
}

void	plus_token(t_tokens tokens, int *ori, int *cp, t_tokens *temp)
{
	char	**divide;
	int		i;

	divide = ft_split(tokens.token[(*ori)], ' ');
	free(tokens.token[(*ori)]);
	i = 0;
	while (divide[i])
	{
		temp->token[(*cp)] = divide[i];
		(*cp)++;
		i++;
	}
	free(divide);
}

t_tokens	env_expand(t_tokens *tokens)
{
	t_tokens	temp;
	int			count;
	int			cp;
	int			ori;

	count = cnt_tok(tokens->token);
	temp.token = ft_calloc(count + 1, sizeof(char *));
	temp.redir = ft_calloc(count + 1, sizeof(int));
	cp = 0;
	ori = 0;
	while (cp < count)
	{
		if (check_space(tokens->token[ori]))
			plus_token(*tokens, &ori, &cp, &temp);
		else
		{
			temp.token[cp] = tokens->token[ori];
			temp.redir[cp] = tokens->redir[ori];
			cp++;
		}
		ori++;
	}
	free(tokens->redir);
	free(tokens->token);
	return (temp);
}
