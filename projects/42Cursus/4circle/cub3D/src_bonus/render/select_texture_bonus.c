/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:51:07 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:51:19 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_dir(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->raydir_y > 0)
			return (1);
		else
			return (0);
	}
	else if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			return (3);
		else
			return (2);
	}
	return (-1);
}

void	calculate_wall_x(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = ray->perpwalldist * ray->raydir_y + data->player.pos_y;
	else
		ray->wall_x = ray->perpwalldist * ray->raydir_x + data->player.pos_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	calculate_texture_x(t_ray *ray)
{
	ray->texture_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->texture_x = TEX_WIDTH - ray->texture_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		ray->texture_x = TEX_WIDTH - ray->texture_x - 1;
}

void	select_texture(t_data *data, t_ray *ray)
{
	ray->tex_num = check_dir(ray);
	calculate_wall_x(data, ray);
	calculate_texture_x(ray);
}
