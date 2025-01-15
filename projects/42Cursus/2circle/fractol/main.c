/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:19:38 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/22 10:55:07 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialize_vals(t_data *data)
{
	data->vals.bottom = -2;
	data->vals.right = 2;
	data->vals.left = -2;
	data->vals.top = 2;
	data->vals.zoom = 1;
	data->img.julia_real = 0.28543;
	data->img.julia_imag = 0.49268;
}

int	window_init(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (FALSE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (data->win == NULL)
		return (FALSE);
	data->img.img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.img_ptr == NULL)
		return (FALSE);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	if (data->img.addr == NULL)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 2)
		print_valid_list();
	ft_memset(&data, 0, sizeof(t_data));
	data.img.set = parse_argv(argv[1]);
	if (data.img.set == INVALID)
		print_valid_list();
	initialize_vals(&data);
	if (data.img.set == JULIA && argc == 4)
	{
		data.img.julia_real = ft_atof(argv[2]);
		data.img.julia_imag = ft_atof(argv[3]);
	}
	if (window_init(&data) == FALSE)
		msg_and_exit("Failed to initialize funcs related to minilibX");
	put_pixel(&data);
	mlx_hook(data.win, X_EVENT_KEY_PRESS, 0, key_hook, &data);
	mlx_hook(data.win, X_EVENT_MOUSE_PRESS, 0, mouse_hook, &data);
	mlx_hook(data.win, X_EVENT_KEY_EXIT, 0, ft_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
