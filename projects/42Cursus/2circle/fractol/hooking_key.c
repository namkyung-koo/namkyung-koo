/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 12:40:53 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/17 18:14:10 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(data->mlx, data->img.img_ptr);
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	data->img.rgb = 0;
	if (keycode == KEY_1)
		data->img.rgb |= CHANGE_R;
	else if (keycode == KEY_2)
		data->img.rgb |= CHANGE_G;
	else if (keycode == KEY_3)
		data->img.rgb |= CHANGE_B;
	else if (keycode == KEY_4)
		data->img.rgb |= CHANGE_ALL;
	else if (keycode == KEY_LEFT)
		data->vals.mv_x -= 0.1 * data->vals.zoom;
	else if (keycode == KEY_RIGHT)
		data->vals.mv_x += 0.1 * data->vals.zoom;
	else if (keycode == KEY_DOWN)
		data->vals.mv_y -= 0.1 * data->vals.zoom;
	else if (keycode == KEY_UP)
		data->vals.mv_y += 0.1 * data->vals.zoom;
	mlx_clear_window(data->mlx, data->win);
	return (put_pixel(data), 0);
}

int	ft_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img_ptr);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
