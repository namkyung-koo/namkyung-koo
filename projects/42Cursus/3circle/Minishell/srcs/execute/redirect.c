/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:03:56 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/20 17:19:34 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	**replace_redir(t_tokens *tokens, int i)
{
	char	**ret;
	int		idx;

	idx = 0;
	while (tokens->token[idx])
		idx++;
	ret = ft_calloc(idx - 1, sizeof(char *));
	idx = 0;
	while (idx < i)
	{
		ret[idx] = tokens->token[idx];
		tokens->redir[idx] = tokens->redir[idx];
		idx++;
	}
	free(tokens->token[i]);
	free(tokens->token[i + 1]);
	while (tokens->token[i + 2])
	{
		ret[idx] = tokens->token[i + 2];
		tokens->redir[idx] = tokens->redir[i + 2];
		idx++;
		i++;
	}
	free(tokens->token);
	return (ret);
}

int	exec_redir(t_tokens *tokens, int i, int flag)
{
	if (flag == IN)
		dup2(open_file(tokens->token[i + 1], READ), STDIN_FILENO);
	else if (flag == OUT)
		dup2(open_file(tokens->token[i + 1], WRITE), STDOUT_FILENO);
	else if (flag == APPEND)
		dup2(open_file(tokens->token[i + 1], HERE_DOC), STDOUT_FILENO);
	tokens->token = replace_redir(tokens, i);
	return (SUCCESS);
}

int	check_redir(t_tokens *tokens, int i)
{
	if (!ft_strcmp(tokens->token[i], "<"))
		exec_redir(tokens, i, IN);
	else if (!ft_strcmp(tokens->token[i], ">"))
		exec_redir(tokens, i, OUT);
	else if (!ft_strcmp(tokens->token[i], ">>"))
		exec_redir(tokens, i, APPEND);
	return (SUCCESS);
}

int	find_redir(t_tokens *tokens, int new_fd, int token_nb, int cmd)
{
	int	i;

	i = 0;
	if (cmd != token_nb - 1)
		dup2(new_fd, STDOUT_FILENO);
	while (tokens->token[i])
	{
		if (tokens->redir[i] == TRUE)
		{
			check_redir(tokens, i);
			i = -1;
		}
		i++;
	}
	return (SUCCESS);
}
