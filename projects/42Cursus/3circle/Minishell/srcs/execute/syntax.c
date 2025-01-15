/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:11:57 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/27 11:39:09 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	each_token(char	**token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "<<") == 0)
		{
			if (token[i + 1] == NULL
				|| token[i + 1][0] == '<'
				|| token[i + 1][0] == '>')
				return (2);
		}
		else if (ft_strcmp(token[i], ">>") == 0)
			if (token[i + 1] == NULL
				|| token[i + 1][0] == '<'
				|| token[i + 1][0] == '>')
				return (2);
		i++;
	}
	return (0);
}

int	syntax_check(t_tokens *tokens, int pipe)
{
	int	i;

	i = 0;
	while (tokens[i].token)
	{
		if (pipe != 0 && tokens[i].token[0] == NULL)
			return (2);
		if (each_token(tokens[i].token))
			return (2);
		pipe--;
		i++;
	}
	if (pipe != -1)
		return (2);
	return (0);
}
