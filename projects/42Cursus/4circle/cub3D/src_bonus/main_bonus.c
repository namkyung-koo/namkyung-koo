/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:52:19 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:53:22 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_heap_section(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->map.height)
		free(data->map.frame[i]);
	i = -1;
	while (++i < SCREEN_HEIGHT)
		free(data->buffer[i]);
	i = -1;
	while (++i < 4)
		free(data->texture[i]);
	free(data->no_texture_path);
	free(data->so_texture_path);
	free(data->we_texture_path);
	free(data->ea_texture_path);
	free(data->map.frame);
	free(data->buffer);
	free(data->texture);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (print_error("The number of argument must be one.", 1, NULL));
	if (check_extension(av[1], "cub") == -1)
		return (print_error("The argument's extension must be cub.", 1, NULL));
	if (open_cub_file(av[1], &data) == -1)
		return (1);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	set_data(&data);
	data.screen_img.img = mlx_new_image(data.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.screen_img.img_data = (int *)mlx_get_data_addr(data.screen_img.img, \
	&data.screen_img.bpp, &data.screen_img.size, &data.screen_img.endian);
	ft_mlx_loop(&data);
	free_heap_section(&data);
	return (0);
}
