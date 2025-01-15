/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:00:09 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/26 00:57: by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	wrong_cmd(char *msg)
{
	perror(msg);
	g_exit = 127;
	return (1);
}

int	cmd_check(t_tokens *tokens, char **envp)
{
	int	i;
	int	j;
	int	buil;
	int	flag;

	i = 0;
	flag = 0;
	buil = 0;
	while (tokens[i].token)
	{
		j = 0;
		while (tokens[i].token[j])
		{
			if (cmd_path(tokens[i].token[j], envp))
				flag = 1;
			j++;
		}
		if (is_builtin(tokens[i]) == 1)
			buil = 1;
		i++;
	}
	if (flag == 1 || buil == 1)
		return (0);
	else
		return (wrong_cmd("minishell"));
}

static void	free_path(char **path, char **cmd)
{
	int	i;

	i = -1;
	if (*cmd != NULL)
		free(*cmd);
	*cmd = NULL;
	while (path[++i])
	{
		free(path[i]);
		path[i] = NULL;
	}
	free(path);
}

static void	free_cmd(char **cmd, char **cmd2)
{
	if (*cmd != NULL)
		free(*cmd);
	*cmd = NULL;
	if (*cmd2 != NULL)
		free(*cmd2);
	*cmd2 = NULL;
}

int	cmd_path(char *check, char **env)
{
	int		i;
	char	*cmd;
	char	*cmd2;
	char	**path;

	path = find_path(env);
	if (path == NULL)
		return (127);
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		cmd = ft_strjoin(path[i], "/");
		cmd2 = ft_strjoin(cmd, check);
		if (access(cmd2, X_OK) == 0)
		{
			free(cmd);
			break ;
		}
		free_cmd(&cmd, &cmd2);
		i++;
	}
	if (access(cmd2, X_OK) == 0 || access(check, X_OK) == 0)
		return (free_path(path, &cmd2), TRUE);
	return (free_path(path, &cmd2), FALSE);
}
