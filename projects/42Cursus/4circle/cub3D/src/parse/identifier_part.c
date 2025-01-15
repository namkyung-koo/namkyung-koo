/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier_part.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:56:30 by nakoo             #+#    #+#             */
/*   Updated: 2023/06/29 15:38:58 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	change_flag(t_data *data, char *identifier)
{
	if (ft_strcmp(identifier, "NO") == 0)
		(data->flag.is_north_texture)++;
	else if (ft_strcmp(identifier, "SO") == 0)
		(data->flag.is_south_texture)++;
	else if (ft_strcmp(identifier, "WE") == 0)
		(data->flag.is_west_texture)++;
	else if (ft_strcmp(identifier, "EA") == 0)
		(data->flag.is_east_texture)++;
	else if (ft_strcmp(identifier, "F") == 0)
		(data->flag.is_floor)++;
	else if (ft_strcmp(identifier, "C") == 0)
		(data->flag.is_ceiling)++;
}

static int	save_texture_path(t_data *data, char **temp)
{
	char	*texture;
	int		fd;

	fd = open(temp[1], O_RDONLY);
	if (fd == -1)
		error_and_exit("Failed to open TEXTURE FILE.");
	close(fd);
	if (fd == -1)
		error_and_exit("Failed to close TEXTURE FILE.");
	if (check_extension(temp[1], "xpm") == -1)
		return (print_error("The texture's extension must be xpm.", -1, NULL));
	texture = ft_strdup(temp[1]);
	if (texture == NULL)
		return (print_error("Failed to allocate memory.", -1, NULL));
	if (data->flag.is_north_texture == 1 && !(data->no_texture_path))
		data->no_texture_path = texture;
	else if (data->flag.is_south_texture == 1 && !(data->so_texture_path))
		data->so_texture_path = texture;
	else if (data->flag.is_west_texture == 1 && !(data->we_texture_path))
		data->we_texture_path = texture;
	else if (data->flag.is_east_texture == 1 && (!data->ea_texture_path))
		data->ea_texture_path = texture;
	else
		return (print_error("There are invaild identifiers.", -1, texture));
	return (0);
}

static int	save_rgb_color(t_data *data, char **temp)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(temp[1], ',');
	if (rgb == NULL)
		return (print_error("Failed to split a RGB part.", -1, NULL));
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
		error_and_exit("RGB part entered wrongly.");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r == -1 || g == -1 || b == -1)
		error_and_exit("RGB part entered wrongly.");
	if (data->flag.is_floor == 1 && data->floor_rgb == -2)
		data->floor_rgb = ((r << 16) + (g << 8) + b);
	else if (data->flag.is_ceiling == 1 && data->ceiling_rgb == -2)
		data->ceiling_rgb = ((r << 16) + (g << 8) + b);
	else
		return (print_error("RGB part entered wrongly.", -1, NULL));
	return (free_2d_array(rgb, 0));
}

int	check_identifier(t_data *data)
{
	if (data->flag.is_floor == 1 && data->flag.is_ceiling == 1 && \
	data->flag.is_south_texture == 1 && data->flag.is_west_texture == 1 && \
	data->flag.is_east_texture == 1 && data->flag.is_north_texture == 1)
		return (1);
	return (0);
}

int	fill_identifier(t_data *data, char *line)
{
	char	**temp;

	temp = ft_split(line, ' ');
	if (temp == NULL)
		return (print_error("Failed to split a line.", -1, NULL));
	if (temp[0] == NULL || temp[1] == NULL || temp[2] != NULL)
		error_and_exit("Some identifier entered wrongly.");
	change_flag(data, temp[0]);
	if (ft_strcmp(temp[0], "NO") == 0 || ft_strcmp(temp[0], "SO") == 0 \
	|| ft_strcmp(temp[0], "WE") == 0 || ft_strcmp(temp[0], "EA") == 0)
	{
		if (save_texture_path(data, temp) == -1)
			exit (1);
	}
	if (ft_strcmp(temp[0], "F") == 0 || ft_strcmp(temp[0], "C") == 0)
	{
		if (save_rgb_color(data, temp) == -1)
			exit (1);
	}
	if (check_identifier(data) == 1)
		data->flag.over_identifier = TRUE;
	return (free_2d_array(temp, 0));
}
