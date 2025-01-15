/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:03:03 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/17 14:45:13 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_n(char *str, int *nl)
{
	int	i;

	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	*nl = NO_NL;
	return (TRUE);
}

int	ft_echo(char **token)
{
	int	nl;
	int	i;

	i = -1;
	nl = NL;
	while (ft_strcmp(token[++i], "echo") != 0)
		;
	if (token[++i] == NULL)
		return (write (1, "\n", 1));
	while (ft_strncmp(token[i], "-n", 2) == 0)
	{
		if (is_n(token[i], &nl) != TRUE)
			break ;
		if (token[++i] == NULL)
			return (write (1, "", 0));
	}
	while (token[i] != NULL)
	{
		write (1, token[i], ft_strlen(token[i]));
		if (token[++i] != NULL && token[i][0] != '\0')
			write (1, " ", 1);
	}
	if (nl != NO_NL)
		write (1, "\n", 1);
	return (TRUE);
}
