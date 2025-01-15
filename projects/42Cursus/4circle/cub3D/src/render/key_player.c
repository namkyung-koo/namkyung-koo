/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:28:30 by jisulee           #+#    #+#             */
/*   Updated: 2023/07/09 19:38:50 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_player_w(t_data *data)
{
	t_player	player;

	player = data->player;
	if (data->map.frame[(int)(player.pos_y \
	+ player.dir_y * (player.move_speed + 0.5))][(int)player.pos_x] == '0')
		data->player.pos_y += player.dir_y * player.move_speed;
	else
		data->player.pos_y -= player.dir_y * player.move_speed;
	if (data->map.frame[(int)player.pos_y][(int)(player.pos_x \
	+ player.dir_x * (player.move_speed + 0.5))] == '0')
		data->player.pos_x += player.dir_x * player.move_speed;
	else
		data->player.pos_x -= player.dir_x * player.move_speed;
}

void	key_player_s(t_data *data)
{
	t_player	player;

	player = data->player;
	if (data->map.frame[(int)(player.pos_y \
	- player.dir_y * (player.move_speed + 0.5))][(int)player.pos_x] == '0')
		data->player.pos_y -= player.dir_y * player.move_speed;
	else
		data->player.pos_y += player.dir_y * player.move_speed;
	if (data->map.frame[(int)player.pos_y][(int)(player.pos_x \
	- player.dir_x * (player.move_speed + 0.5))] == '0')
		data->player.pos_x -= player.dir_x * player.move_speed;
	else
		data->player.pos_x += player.dir_x * player.move_speed;
}

void	key_player_a(t_data *data)
{
	t_player	player;

	player = data->player;
	if (data->map.frame[(int)(player.pos_y \
	- player.plane_y * (player.move_speed + 0.5))][(int)player.pos_x] == '0')
		data->player.pos_y -= player.plane_y * player.move_speed;
	else
		data->player.pos_y += player.plane_y * player.move_speed;
	if (data->map.frame[(int)player.pos_y][(int)(player.pos_x \
	- player.plane_x * (player.move_speed + 0.5))] == '0')
		data->player.pos_x -= player.plane_x * player.move_speed;
	else
		data->player.pos_x += player.plane_x * player.move_speed;
}

void	key_player_d(t_data *data)
{
	t_player	player;

	player = data->player;
	if (data->map.frame[(int)(player.pos_y \
	+ player.plane_y * (player.move_speed + 0.5))][(int)player.pos_x] == '0')
		data->player.pos_y += player.plane_y * player.move_speed;
	else
		data->player.pos_y -= player.plane_y * player.move_speed;
	if (data->map.frame[(int)player.pos_y][(int)(player.pos_x \
	+ player.plane_x * (player.move_speed + 0.5))] == '0')
		data->player.pos_x += player.plane_x * player.move_speed;
	else
		data->player.pos_x -= player.plane_x * player.move_speed;
}
