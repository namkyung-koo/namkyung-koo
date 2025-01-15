/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:40:37 by jisulee           #+#    #+#             */
/*   Updated: 2023/07/10 16:37:41 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_texture_arr(t_data *data)
{
	int	idx;

	data->texture = (int **)malloc(sizeof(int *) * 4);
	if (!data->texture)
		exit (1);
	idx = 0;
	while (idx < 4)
	{
		data->texture[idx] = (int *) \
		malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
		if (!data->texture[idx])
			exit (1);
		idx++;
	}
}

void	load_image(t_data *data, t_image *image, int *texture, char *path)
{
	int	i;
	int	j;

	image->img = mlx_xpm_file_to_image(data->mlx, path, &image->img_width, \
	&image->img_height);
	if (image->img == NULL)
		error_and_exit("xpm file is invalid.");
	image->img_data = (int *)mlx_get_data_addr(image->img, &image->bpp, \
	&image->size, &image->endian);
	i = 0;
	while (i < TEX_HEIGHT)
	{
		j = 0;
		while (j < TEX_WIDTH)
		{
			texture[image->img_width * i + j] = \
			image->img_data[image->img_width * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(data->mlx, image->img);
}

void	load_texture(t_data *data)
{
	load_image(data, &(data->screen_img), data->texture[0], \
	data->no_texture_path);
	load_image(data, &(data->screen_img), data->texture[1], \
	data->so_texture_path);
	load_image(data, &(data->screen_img), data->texture[2], \
	data->we_texture_path);
	load_image(data, &(data->screen_img), data->texture[3], \
	data->ea_texture_path);
}
