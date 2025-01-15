/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:21:49 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/10 10:58:54 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_space(char **line)
{
	while ((**line) == ' ')
		(*line)++;
}

void	init_t_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->floor_rgb = -2;
	data->ceiling_rgb = -2;
}

void	get_height_and_width(t_data *data)
{
	t_node	*temp;
	int		max;

	if (data->map.list == NULL)
		error_and_exit("The file's format entered wrongly.");
	temp = data->map.list->head_node.next;
	max = 0;
	while (temp != NULL)
	{
		max = ft_strlen(temp->content);
		if (max > data->map.width)
			data->map.width = max;
		temp = temp->next;
	}
	data->map.height = data->map.list->node_count;
}

void	duplicate_to_array(t_data *data)
{
	t_node	*temp;
	t_node	*del_node;
	int		i;

	get_height_and_width(data);
	data->map.arr = (char **)malloc(sizeof(char *) * (data->map.height + 1));
	if (data->map.arr == NULL)
		error_and_exit("Failed to allocate memory.");
	data->map.arr[data->map.height] = NULL;
	i = 0;
	temp = data->map.list->head_node.next;
	while (i < data->map.height && temp != NULL)
	{
		del_node = temp;
		data->map.arr[i] = ft_strndup(temp->content, data->map.width);
		temp = temp->next;
		free(del_node->content);
		free(del_node);
		i++;
	}
	free(data->map.list);
}

void	chararr_to_intarr(t_data *data)
{
	int	i;
	int	j;

	data->map.frame = (int **)malloc(sizeof(int *) * data->map.height);
	if (data->map.frame == NULL)
		error_and_exit("Failed to allocate memory.");
	i = -1;
	while (++i < data->map.height)
	{
		data->map.frame[i] = (int *)malloc(sizeof(int) * \
		ft_strlen(data->map.arr[i]));
		if (data->map.frame[i] == NULL)
			error_and_exit("Failed to allocate memory.");
		j = -1;
		while (++j < data->map.width)
		{
			if (data->map.arr[i][j] == 'E' || data->map.arr[i][j] == 'W'
				|| data->map.arr[i][j] == 'N' || data->map.arr[i][j] == 'S')
				data->map.frame[i][j] = '0';
			else
				data->map.frame[i][j] = data->map.arr[i][j];
		}
		free(data->map.arr[i]);
	}
	free(data->map.arr);
}
