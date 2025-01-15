/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:46:42 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:47:05 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	print_error(char *msg, int return_value, char *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (return_value);
}

int	free_2d_array(char **ptr, int return_value)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (return_value);
}

int	check_extension(char *str, const char *extension)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (str[i] == '.')
		i++;
	while (str[i] != '\0' && ft_isprint(str[i]) != 0)
	{
		if (str[i] == '.')
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (-1);
	else
	{
		++i;
		if (ft_strcmp(&str[i], extension) != 0)
			return (-1);
	}
	return (0);
}

void	newline_to_null(char *line)
{
	int	i;

	i = 0;
	while (*(line + i) != '\n' && *(line + i) != '\0')
		i++;
	if (*(line + i) == '\n')
		*(line + i) = '\0';
}

void	error_and_exit(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit (1);
}
