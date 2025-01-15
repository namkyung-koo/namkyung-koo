/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_wall_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:48:57 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:49:11 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_start_and_endpoint(t_ray *ray)
{
	ray->start_point = ((SCREEN_HEIGHT / 2) - (ray->line_height / 2));
	if (ray->start_point < 0)
		ray->start_point = 0;
	ray->end_point = ((ray->line_height / 2) + (SCREEN_HEIGHT / 2));
	if (ray->end_point >= SCREEN_HEIGHT)
		ray->end_point = SCREEN_HEIGHT - 1;
}

double	calculate_perpwalldist(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map_x - player->pos_x + \
		(1 - ray->step_x) / 2) / ray->raydir_x);
	else
		return ((ray->map_y - player->pos_y + \
		(1 - ray->step_y) / 2) / ray->raydir_y);
}

void	calculate_wall(t_player *player, t_ray *ray)
{
	ray->perpwalldist = calculate_perpwalldist(player, ray);
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perpwalldist);
	calculate_start_and_endpoint(ray);
}
