/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:19:21 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/26 00:56:07 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	here_doc(t_tokens *tokens, int i, char *name, int *flag)
{
	char	*line;
	char	*limiter;
	int		fd;
	int		save;

	fd = open_file(name, WRITE);
	limiter = ft_strjoin(tokens->token[i + 1], "\n");
	save = dup(STDIN_FILENO);
	setting_signal(HEREDOC);
	while (write(1, "> ", 2))
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			*flag = 1;
		if (line == NULL || ft_strcmp(line, limiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	dup2(save, STDIN_FILENO);
	return (free(limiter), free(line));
}

int	save_filename(t_tokens *tokens, char **name, int *file_n, int i)
{
	char	*num;
	int		flag;

	flag = 0;
	num = ft_itoa((*file_n));
	name[(*file_n)] = ft_strjoin(tokens->token[i + 1], num);
	free(num);
	here_doc(tokens, i, name[(*file_n)], &flag);
	if (flag == 1)
		return (1);
	replace_here_doc(tokens, i, file_n);
	return (0);
}

char	**name_save(t_tokens *tokens)
{
	char	**name;
	int		i;
	int		j;
	int		num;

	i = 0;
	num = 0;
	while (tokens[i].token)
	{
		j = 0;
		while (tokens[i].token[j])
		{
			if (ft_strcmp(tokens[i].token[j], "<<") == 0)
				num++;
			j++;
		}
		i++;
	}
	name = ft_calloc(num + 1, sizeof(char *));
	return (name);
}

void	replace_here_doc(t_tokens *tokens, int i, int *file_n)
{
	char	*num;
	char	*temp;

	num = ft_itoa((*file_n));
	free(tokens->token[i]);
	tokens->token[i] = ft_strdup("<");
	temp = tokens->token[i + 1];
	tokens->token[i + 1] = ft_strjoin(temp, num);
	free(temp);
	free(num);
	(*file_n)++;
}

char	**find_here_doc(t_tokens *tokens, int *flag, char **env)
{
	int		i[2];
	int		file_n;
	char	**name;

	i[0] = -1;
	file_n = 0;
	name = name_save(tokens);
	while (tokens[++i[0]].token)
	{
		i[1] = -1;
		while (tokens[i[0]].token[++i[1]])
		{
			if (ft_strcmp(tokens[i[0]].token[i[1]], "<<") == 0)
			{
				if (save_filename(&tokens[i[0]], name, &file_n, i[1]) == 1)
				{
					*flag = 1;
					return (name);
				}
			}
		}
	}
	if (cmd_check(tokens, env))
		*flag = 1;
	return (name);
}
