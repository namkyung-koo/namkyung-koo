/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_part_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:45:43 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:45:55 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	check_border(t_data *data, int x, int y)
{
	if ((data->map.arr[0][x] != '1' && data->map.arr[0][x] != ' ') \
	|| (data->map.arr[data->map.height - 1][x] != '1' && \
	data->map.arr[data->map.height - 1][x] != ' ') \
	|| (data->map.arr[y][0] != '1' && data->map.arr[y][0] != ' ') \
	|| (data->map.arr[y][data->map.width - 1] != '1' && \
	data->map.arr[y][data->map.width - 1] != ' '))
		error_and_exit("The map must be surrounded by walls.");
}

static void	check_4_dir(int x, int y, char *ptr, t_data *data)
{
	if (*ptr == 'N')
		data->map.view_dir = NORTH;
	else if (*ptr == 'S')
		data->map.view_dir = SOUTH;
	else if (*ptr == 'W')
		data->map.view_dir = WEST;
	else if (*ptr == 'E')
		data->map.view_dir = EAST;
	if (*ptr != '0')
	{
		(data->map.player)++;
		if (data->map.player != 1)
			error_and_exit("please, check the number of player.");
		data->map.player_x = x;
		data->map.player_y = y;
	}
	check_border(data, x, y);
	if (x - 1 < 0 || x + 1 > data->map.width || \
	y - 1 < 0 || y + 1 > data->map.height)
		return ;
	else if (data->map.arr[y - 1][x] == ' ' \
	|| data->map.arr[y + 1][x] == ' ' \
	|| data->map.arr[y][x - 1] == ' ' \
	|| data->map.arr[y][x + 1] == ' ')
		error_and_exit("The map part entered wrongly.");
}

void	check_map_data(t_data *data)
{
	char	*ptr;
	int		x;
	int		y;

	duplicate_to_array(data);
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			ptr = ft_strchr("01 NSWE", data->map.arr[y][x]);
			if (ptr != NULL)
			{
				if (*ptr == 'N' || *ptr == 'S' || *ptr == 'W' || *ptr == 'E' \
				|| *ptr == '0')
					check_4_dir(x, y, ptr, data);
			}
			else
				error_and_exit("please, check the component of map.");
		}
	}
	if (data->map.player == 0)
		error_and_exit("Player doesn't exist.");
	chararr_to_intarr(data);
}
