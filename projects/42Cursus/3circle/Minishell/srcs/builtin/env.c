/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:03 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/22 19:47:26 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (ft_strfind(env, "PATH") == NULL)
	{
		printf("minishell: env: No such file or directory\n");
		g_exit = 127;
		return (g_exit);
	}
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
			printf("%s\n", env[i]);
		i++;
	}
	return (g_exit);
}
