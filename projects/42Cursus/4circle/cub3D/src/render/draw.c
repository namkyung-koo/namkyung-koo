/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:04:49 by jisulee           #+#    #+#             */
/*   Updated: 2023/07/09 19:37:24 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			data->screen_img.img_data[y * SCREEN_WIDTH + x] = \
			data->buffer[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen_img.img, 0, 0);
}

void	draw_floor_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				data->buffer[y][x] = data->ceiling_rgb;
			else
				data->buffer[y][x] = data->floor_rgb;
			x++;
		}
		y++;
	}
}

void	make_buffer(t_data *data, t_ray *ray, int screen_x)
{
	double	step;
	double	texture_pos;
	int		texture_y;
	int		y;

	step = 1.0 * TEX_HEIGHT / ray->line_height;
	texture_pos = \
	(ray->start_point - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->start_point;
	while (y < ray->end_point)
	{
		texture_y = (int)texture_pos & (TEX_HEIGHT - 1);
		texture_pos += step;
		data->buffer[y][screen_x] = \
		data->texture[ray->tex_num][TEX_HEIGHT * texture_y + ray->texture_x];
		y++;
	}
}
