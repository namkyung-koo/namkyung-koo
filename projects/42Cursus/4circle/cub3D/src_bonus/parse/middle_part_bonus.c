/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_part_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:46:08 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:46:22 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_map_part(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == '1')
		{
			data->flag.is_map = TRUE;
			return (1);
		}
		else if (line[i] == ' ')
			i++;
		else
			error_and_exit("File contents are invalid.");
	}
	return (0);
}

static void	save_line_to_list(t_data *data, char *line)
{
	char	*temp;
	t_node	*new;

	if (data->map.list == NULL)
	{
		data->map.list = ft_lstcreate();
		if (data->map.list == NULL)
			error_and_exit("Failed to allocate memory.");
	}
	temp = ft_strdup(line);
	new = ft_lstnew(temp);
	if (new == NULL)
		error_and_exit("Failed to allocate memory.");
	ft_lstadd_back(data->map.list, new);
}

int	fill_map(t_data *data, char *line)
{
	if (data->flag.over_identifier && !(data->flag.is_map))
	{
		if (is_map_part(data, line) == 0)
			return (0);
	}
	if (data->flag.over_identifier && data->flag.is_map)
		save_line_to_list(data, line);
	return (0);
}
