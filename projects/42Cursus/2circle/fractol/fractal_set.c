/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:24:01 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/22 17:29:41 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(int iter, t_data *data)
{
	double	c_re;
	double	c_im;
	double	z_re_new;
	double	z_re;
	double	z_im;

	c_re = data->vals.count_w * ((data->vals.right - data->vals.left) \
					/ (double)WIDTH) + data->vals.left + data->vals.mv_x;
	c_im = data->vals.count_h * ((data->vals.bottom - data->vals.top) \
					/ (double)HEIGHT) + data->vals.top + data->vals.mv_y;
	z_re = 0;
	z_im = 0;
	while ((z_re * z_re) + (z_im * z_im) < 4 && iter < MAX_ITERATION)
	{
		z_re_new = (z_re * z_re) - (z_im * z_im) + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re_new;
		iter++;
	}
	my_mlx_pixel_put(data, color_set(iter, data));
	return (iter);
}

int	julia(int iter, t_data *data)
{
	double	c_re;
	double	c_im;
	double	z_re_new;
	double	z_re;
	double	z_im;

	c_re = data->img.julia_real;
	c_im = data->img.julia_imag;
	z_re = data->vals.count_w * ((data->vals.right - data->vals.left) \
					/ (double)WIDTH) + data->vals.left + data->vals.mv_x;
	z_im = data->vals.count_h * ((data->vals.bottom - data->vals.top) \
					/ (double)HEIGHT) + data->vals.top + data->vals.mv_y;
	while ((z_re * z_re) + (z_im * z_im) < 4 && iter < MAX_ITERATION)
	{
		z_re_new = (z_re * z_re) - (z_im * z_im) + c_re;
		z_im = 2 * z_re * z_im + c_im;
		z_re = z_re_new;
		iter++;
	}
	my_mlx_pixel_put(data, color_set(iter, data));
	return (iter);
}

int	burningship(int iter, t_data *data)
{
	double	c_re;
	double	c_im;
	double	z_re_new;
	double	z_re;
	double	z_im;

	c_re = data->vals.count_w * ((data->vals.right - data->vals.left) \
					/ (double)WIDTH) + data->vals.left + data->vals.mv_x;
	c_im = data->vals.count_h * ((data->vals.bottom - data->vals.top) \
					/ (double)HEIGHT) + data->vals.top + data->vals.mv_y;
	z_re = 0;
	z_im = 0;
	while ((z_re * z_re) + (z_im * z_im) < 4 && iter < MAX_ITERATION)
	{
		z_re_new = z_re * z_re - z_im * z_im + c_re;
		z_im = -2 * fabs(z_re) * fabs(z_im) + c_im;
		z_re = z_re_new;
		iter++;
	}
	my_mlx_pixel_put(data, color_set(iter, data));
	return (iter);
}
