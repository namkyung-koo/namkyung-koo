/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 09:39:56 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/22 08:50:17 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	get_end_with_len(char **loca, char **finish, char **env)
{
	char	*find_env;
	char	*env_name;
	int		env_len;
	int		len;

	len = 0;
	env_len = 0;
	(*finish) = (*loca);
	while (ft_isalnum(**finish) || **finish == '_')
	{
		len++;
		(*finish)++;
	}
	env_name = ft_substr(*loca, 0, len);
	find_env = ft_strfind(env, env_name);
	while (find_env != NULL && find_env[env_len])
		env_len++;
	env_len -= (len + 1);
	free(env_name);
	return (env_len);
}

char	*make_ret(char **loca, char *origin, char **env, char **finish)
{
	int		first;
	int		env_len;
	int		last;

	first = 0;
	last = 0;
	while (origin[first] != '$')
		first++;
	env_len = get_end_with_len(loca, finish, env);
	if (env_len < 0)
		env_len = 1;
	while ((*finish)[last])
		last++;
	return (ft_calloc(first + env_len + last + 1, sizeof(char)));
}

int	get_len(char *str, int position)
{
	int	len;

	len = 0;
	if (position == 0)
		while (str[len] != '$')
			len++;
	else if (position == 1)
		while (ft_isalnum(str[len]) || str[len] == '_')
			len++;
	else if (position == 2)
		while (str[len])
			len++;
	return (len);
}

char	*replace_env(char **loca, char *origin, char **env)
{
	char	*ret;
	char	*finish;
	char	*find_env;
	char	*env_name;
	int		len;

	ret = make_ret(loca, origin, env, &finish);
	len = get_len(origin, 0);
	ft_memmove(ret, origin, len);
	len = get_len(*loca, 1);
	env_name = ft_substr(*loca, 0, len);
	find_env = ft_strfind(env, env_name);
	if (find_env != NULL)
		ft_memmove(ret + get_len(origin, 0), find_env + len + 1,
			ft_strlen(find_env + len + 1));
	len = get_len(ret, 2);
	*loca = ret + len;
	ft_memmove(ret + get_len(ret, 2), finish, ft_strlen(finish));
	free(env_name);
	free(origin);
	return (ret);
}

void	check_env(t_tokens *tokens, char **env)
{
	char	*loca;
	char	*temp;
	int		i;

	i = 0;
	while (tokens->token[i])
	{
		loca = tokens->token[i];
		temp = tokens->token[i];
		while (env_qut_check(temp) && loca)
		{
			loca = ft_strchr(loca, '$');
			if (loca != NULL && (ft_isalnum(*(++loca)) || *loca == '_'))
			{
				if (ft_isdigit(*loca))
					ft_memmove(loca - 1, loca + 1, ft_strlen(loca));
				else
					tokens->token[i]
						= replace_env(&loca, tokens->token[i], env);
			}
			else if (loca != NULL && *loca == '?')
				tokens->token[i] = re_quo(&loca, tokens->token[i]);
		}
		i++;
	}
}
