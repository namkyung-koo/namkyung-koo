/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:03 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/23 17:53:08 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	add_env(char **env, const char *find, char *str, int flag)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(find);
	while (ft_strncmp(env[i], find, len) != 0)
		i++;
	if (env[i] == NULL)
		return (FALSE);
	free(env[i]);
	while (env[i + 1] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}
	tmp = ft_strjoin(find, str);
	env[i] = tmp;
	env[i + 1] = NULL;
	if (flag == 1)
		free(str);
	return (TRUE);
}

static int	move_home_dir(char **env)
{
	char	*pwd;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "HOME=", 5) != 0)
		i++;
	pwd = &env[i][5];
	error_msg(chdir(pwd) == 0, "cd ");
	return (add_env(env, "PWD=", pwd, 0));
}

static int	move_token_dir(char *pwd)
{
	return (error_msg(chdir(pwd) == 0, "cd "));
}

int	ft_cd(char **tok, char **env)
{
	char	*copy;
	char	*pwd;
	int		i;

	i = -1;
	while (ft_strcmp(tok[++i], "cd") != 0)
		;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = ft_strdup("");
	if (add_env(env, "OLDPWD=", pwd, 1) == FALSE)
		return (free(pwd), FALSE);
	copy = ft_strdup(ft_strfind(env, "OLDPWD") + 7);
	if (tok[i + 1] == NULL)
		return (free(copy), move_home_dir(env));
	else if (tok[i + 1] != NULL)
	{
		move_token_dir(tok[i + 1]);
		pwd = getcwd(NULL, 0);
	}
	if (add_env(env, "PWD=", pwd, 1) == FALSE)
		return (free(copy), FALSE);
	return (free(copy), g_exit);
}
