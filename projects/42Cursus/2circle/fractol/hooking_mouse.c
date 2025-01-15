/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:41:49 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/21 20:22:01 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == MOUSE_SCROLL_DOWN)
		data->vals.zoom *= 0.9;
	else if (button == MOUSE_SCROLL_UP)
		data->vals.zoom *= 1.1;
	data->vals.mouse_x = x;
	data->vals.mouse_y = y;
	mlx_clear_window(data->mlx, data->win);
	mouse_zoom(data);
	return (0);
}

void	mouse_zoom(t_data *data)
{
	double	new_width;
	double	new_height;
	double	x_len;
	double	y_len;

	data->vals.set_height = 4;
	data->vals.set_width = 4;
	new_width = data->vals.zoom * data->vals.set_width;
	new_height = -1 * data->vals.zoom * data->vals.set_height;
	x_len = data->vals.right - data->vals.left;
	y_len = data->vals.bottom - data->vals.top;
	data->vals.left = data->vals.left + \
				data->vals.mouse_x * x_len / (double)WIDTH - \
					data->vals.mouse_x * (new_width / (double)WIDTH);
	data->vals.top = data->vals.top \
				+ data->vals.mouse_y * y_len / (double)HEIGHT - \
					data->vals.mouse_y * (new_height / (double)HEIGHT);
	data->vals.right = data->vals.left + new_width;
	data->vals.bottom = data->vals.top + new_height;
	put_pixel(data);
}
