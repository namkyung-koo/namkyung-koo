/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:03 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/23 14:58:27 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	find_unset(char **token)
{
	int	i;

	i = 0;
	while (ft_strcmp(token[i], "unset") != 0)
		i++;
	return (i);
}

static int	get_del_idx(char *token, char **env, int *del_idx)
{
	int	len;

	*del_idx = 0;
	while (env[*del_idx] != NULL)
	{
		len = 0;
		while (env[*del_idx][len] != '\0' && env[*del_idx][len] != '=')
			len++;
		if (ft_strncmp(token, env[*del_idx], len) == 0)
			return (*del_idx);
		(*del_idx)++;
	}
	return (FALSE);
}

int	ft_unset(char **token, char **env)
{
	int	i;
	int	del_idx;

	i = find_unset(token);
	while (token[++i] != NULL)
	{
		if (ft_isalpha(token[i][0]) == 0 && token[i][0] != '_')
			return (!printf("minishell: unset: `%s': not a valid identifier\n", \
			token[i]));
		else
		{
			if (get_del_idx(token[i], env, &del_idx) != FALSE)
			{
				free(env[del_idx]);
				while (env[del_idx + 1] != NULL)
				{
					env[del_idx] = env[del_idx + 1];
					del_idx++;
				}
				env[del_idx] = NULL;
			}
		}
	}
	return (TRUE);
}
