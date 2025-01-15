/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 19:18:22 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/23 14:41:21 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_pipe(char *line)
{
	int	qut;
	int	db_qut;
	int	pipe_num;

	qut = 0;
	db_qut = 0;
	pipe_num = 0;
	while (*line)
	{
		if (*line == '\'')
			qut = ~qut;
		else if (*line == '\"')
			db_qut = ~db_qut;
		if (*line == '|' && qut == 0 && db_qut == 0)
			pipe_num++;
		line++;
	}
	return (pipe_num);
}

int	until_pipe(char *line)
{
	int	len;
	int	qut;
	int	db_qut;

	len = 0;
	qut = 0;
	db_qut = 0;
	while (line[len] != '\0')
	{
		if (line[len] == '\'')
			qut = ~qut;
		else if (line[len] == '\"')
			db_qut = ~db_qut;
		if (line[len] == '|' && qut == 0 && db_qut == 0)
			break ;
		len++;
	}
	return (len);
}

int	parsing(char *line, t_tokens **tokens, char **env)
{
	char	*token;
	int		tokens_n;
	int		token_len;
	int		idx;

	tokens_n = get_pipe(line) + 1;
	*tokens = ft_calloc(tokens_n + 1, sizeof(t_tokens));
	idx = 0;
	while (*line)
	{
		token_len = until_pipe(line);
		token = ft_substr(line, 0, token_len);
		(*tokens)[idx].token = split_token(token);
		(*tokens)[idx].redir = ft_calloc(cnt_tokens(token), sizeof(int));
		is_redir(tokens, idx, cnt_tokens(token));
		check_env(&(*tokens)[idx], env);
		(*tokens)[idx] = env_expand(&(*tokens)[idx]);
		check_quote(&(*tokens)[idx]);
		idx++;
		line += token_len;
		if (*line == '|')
			line++;
		free(token);
	}
	return (tokens_n - 1);
}
