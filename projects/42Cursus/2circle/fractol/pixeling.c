/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixeling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:12:36 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/21 20:52:06 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_set(int iter, t_data *data)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = 10;
	g = 15;
	b = 15;
	if (data->img.rgb & CHANGE_R)
		r = 15;
	else if (data->img.rgb & CHANGE_G)
		g = 20;
	else if (data->img.rgb & CHANGE_B)
		b = 20;
	color = 0;
	if (!(iter < MAX_ITERATION))
		return (color);
	color = \
		((r * iter) % 256 << 16) + ((g * iter) % 256 << 8) + ((b * iter) % 256);
	return (color);
}

void	my_mlx_pixel_put(t_data *data, int color)
{
	char	*dst;

	dst = data->img.addr + (data->vals.count_h * data->img.line_length \
						+ data->vals.count_w * (data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_pixel(t_data *data)
{
	int	(*f_ptr)(int, t_data*);

	if (data->img.set == MANDELBROT)
		f_ptr = mandelbrot;
	else if (data->img.set == JULIA)
		f_ptr = julia;
	else
		f_ptr = burningship;
	data->vals.count_h = 0;
	while (data->vals.count_h < HEIGHT)
	{
		data->vals.count_w = 0;
		while (data->vals.count_w < WIDTH)
		{
			f_ptr(0, data);
			data->vals.count_w++;
		}
		data->vals.count_h++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
