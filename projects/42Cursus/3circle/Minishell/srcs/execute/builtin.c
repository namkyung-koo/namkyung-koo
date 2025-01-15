/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:44:06 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/23 18:08:39 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(t_tokens tokens)
{
	int	i;

	i = 0;
	while (tokens.token[i])
	{
		if (ft_strcmp(tokens.token[i], "export") == 0)
			return (TRUE);
		else if (ft_strcmp(tokens.token[i], "unset") == 0)
			return (TRUE);
		else if (ft_strcmp(tokens.token[i], "cd") == 0)
			return (TRUE);
		else if (ft_strcmp(tokens.token[i], "pwd") == 0)
			return (TRUE);
		else if (ft_strcmp(tokens.token[i], "env") == 0)
			return (TRUE);
		else if (ft_strcmp(tokens.token[i], "echo") == 0)
			return (TRUE);
		else if (ft_strcmp(tokens.token[i], "exit") == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	exec_builtin(t_tokens *tokens, char **dup_env)
{
	int	j;

	j = 0;
	setting_signal(PARENT_EXECVE);
	while (tokens->token[j] != NULL)
	{
		if (ft_strcmp(tokens->token[j], "export") == 0)
			return (!ft_export(tokens->token, dup_env));
		else if (ft_strcmp(tokens->token[j], "unset") == 0)
			return (!ft_unset(tokens->token, dup_env));
		else if (ft_strcmp(tokens->token[j], "cd") == 0)
			return (ft_cd(tokens->token, dup_env));
		else if (ft_strcmp(tokens->token[j], "pwd") == 0)
			return (!ft_pwd(dup_env));
		else if (ft_strcmp(tokens->token[j], "env") == 0)
			return (ft_env(dup_env));
		else if (ft_strcmp(tokens->token[j], "echo") == 0)
			return (!ft_echo(tokens->token));
		else if (ft_strcmp(tokens->token[j], "exit") == 0)
			ft_exit(tokens->token);
		j++;
	}
	return (FALSE);
}
