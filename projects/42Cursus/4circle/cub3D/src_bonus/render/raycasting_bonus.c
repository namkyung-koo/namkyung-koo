/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:50:52 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:51:03 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_sidedist(t_player *player, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

void	set_ray(t_player *player, t_ray *ray, int screen_x)
{
	ray->camera_x = (2 * screen_x / (double)SCREEN_WIDTH) - 1;
	ray->raydir_x = player->dir_x + (ray->camera_x * player->plane_x);
	ray->raydir_y = player->dir_y + (ray->camera_x * player->plane_y);
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	if (ray->raydir_y == 0)
		ray->deltadist_x = 0;
	else
	{
		if (ray->raydir_x == 0)
			ray->deltadist_x = 1;
		else
			ray->deltadist_x = fabs(1 / ray->raydir_x);
	}
	if (ray->raydir_x == 0)
		ray->deltadist_y = 0;
	else
	{
		if (ray->raydir_y == 0)
			ray->deltadist_y = 1;
		else
			ray->deltadist_y = fabs(1 / ray->raydir_y);
	}
	ray->hit = 0;
	set_sidedist(player, ray);
}

void	dda_algorithms(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->frame[ray->map_y][ray->map_x] > '0')
			ray->hit = 1;
	}
}

void	raycasting(t_data *data)
{
	int	screen_x;

	screen_x = 0;
	while (screen_x < SCREEN_WIDTH)
	{
		set_ray(&(data->player), &(data->ray), screen_x);
		dda_algorithms(&(data->ray), &(data->map));
		calculate_wall(&(data->player), &(data->ray));
		select_texture(data, &data->ray);
		make_buffer(data, &data->ray, screen_x);
		screen_x++;
	}
}
