/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:47:49 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/14 14:43:42 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	is_redir(t_tokens **tok, int idx, int token_num)
{
	int	i;
	int	len;

	i = 0;
	while (i < token_num)
	{
		len = 0;
		while ((*tok)[idx].token[i][len])
			len++;
		if (len == 1
			&& ((*tok)[idx].token[i][0] == '<'
			|| (*tok)[idx].token[i][0] == '>'))
			(*tok)[idx].redir[i] = TRUE;
		else if (len == 2
			&& (((*tok)[idx].token[i][0] == '<'
			&& (*tok)[idx].token[i][1] == '<')
			|| ((*tok)[idx].token[i][0] == '>'
			&& (*tok)[idx].token[i][1] == '>')))
			(*tok)[idx].redir[i] = TRUE;
		i++;
	}
}
