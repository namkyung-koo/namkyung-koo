/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:03 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/23 16:39:59 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	variable_init(int **sorted_idx, int *sign, int *i, int *j)
{
	*sorted_idx = NULL;
	*sign = 0;
	*i = -1;
	*j = 0;
}

static int	*sort_ascii(char **env)
{
	int	*sorted_idx;
	int	idx;
	int	i;
	int	j;

	idx = 0;
	while (env[idx] != NULL)
		idx++;
	sorted_idx = (int *)malloc(sizeof(int) * idx);
	idx = -1;
	while (env[++idx] != NULL)
		sorted_idx[idx] = idx;
	i = -1;
	while (++i < idx - 1)
	{
		j = i + 1;
		while (++j < idx)
		{
			if (ft_strcmp(env[sorted_idx[i]], env[sorted_idx[j]]) > 0)
				swap(&sorted_idx[i], &sorted_idx[j]);
		}
	}
	return (sorted_idx);
}

static int	print_export(char **dup_env, int *sorted_idx, int sign)
{
	int	i;
	int	j;

	sorted_idx = sort_ascii(dup_env);
	i = -1;
	while (dup_env[++i] != NULL)
	{
		j = -1;
		printf("declare -x ");
		sign = NO_EQUAL;
		while (dup_env[sorted_idx[i]][++j] != '\0')
		{
			if (dup_env[sorted_idx[i]][j] == '=' && sign == NO_EQUAL)
			{
				sign = EQUAL;
				printf("=\"");
			}
			else
				printf("%c", dup_env[sorted_idx[i]][j]);
		}
		if (sign == EQUAL)
			printf("\"");
		printf("\n");
	}
	return (free(sorted_idx), TRUE);
}

static void	is_duplicated(char *str, char **dup_env)
{
	int	len;
	int	i;

	i = 0;
	while (dup_env[i] != NULL)
	{
		len = 0;
		while (dup_env[i][len] != '=' && dup_env[i][len] != '\0')
			len++;
		if (ft_strncmp(str, dup_env[i], len) == 0)
			break ;
		i++;
	}
	if (dup_env[i] != NULL)
	{
		free(dup_env[i]);
		while (dup_env[i + 1] != NULL)
		{
			dup_env[i] = dup_env[i + 1];
			i++;
		}
		dup_env[i] = NULL;
	}
}

int	ft_export(char **token, char **dup_env)
{
	int	*sorted_idx;
	int	sign;
	int	i;
	int	j;

	variable_init(&sorted_idx, &sign, &i, &j);
	while (ft_strcmp(token[++i], "export") != 0)
		;
	if (token[i + 1] == NULL)
		return (print_export(dup_env, sorted_idx, sign));
	while (token[++i] != NULL)
	{
		if (ft_isalpha(token[i][0]) == 0 && token[i][0] != '_')
			return (!printf("minishell: export: `%s': not a valid identifier\n", \
			token[i]));
		else
		{
			is_duplicated(token[i], dup_env);
			while (dup_env[j] != NULL)
				j++;
			dup_env[j] = ft_strdup(token[i]);
			dup_env[j + 1] = NULL;
		}
	}
	return (TRUE);
}
