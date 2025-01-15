/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:41:23 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/09 19:42:55 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "enum.h"
# include "structure.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

// utils_bonus.c
int		free_2d_array(char **ptr, int return_value);
int		check_extension(char *str, const char *extension);
int		print_error(char *msg, int return_value, char *ptr);
void	error_and_exit(char *msg);
void	newline_to_null(char *line);

// file_validation_bonus.c
int		open_cub_file(const char *cub_file, t_data *data);

// identifier_part_bonus.c
int		check_identifier(t_data *data);
int		fill_identifier(t_data *data, char *line);

// middle_part_bonus.c
int		fill_map(t_data *data, char *line);

// map_part_bonus.c
void	check_map_data(t_data *data);

// set_value_utils_bonus.c
void	skip_space(char **line);
void	init_t_data(t_data *data);
void	get_height_and_width(t_data *data);
void	duplicate_to_array(t_data *data);
void	chararr_to_intarr(t_data *data);

// calculate_wall_bonus.c
void	calculate_start_and_endpoint(t_ray *ray);
void	calculate_wall(t_player *player, t_ray *ray);
double	calculate_perpwalldist(t_player *player, t_ray *ray);

// draw_bonus.c
void	draw_map(t_data *data);
void	draw_floor_ceiling(t_data *data);
void	make_buffer(t_data *data, t_ray *ray, int screen_x);

// load_texture_bonus.c
void	load_texture(t_data *data);
void	make_texture_arr(t_data *data);
void	load_image(t_data *data, t_image *image, int *texture, char *path);

// main_loop_bonus.c
int		main_loop(t_data *data);
void	ft_mlx_loop(t_data *data);

// raycasting_bonus.c
void	raycasting(t_data *data);
void	dda_algorithms(t_ray *ray, t_map *map);
void	set_sidedist(t_player *player, t_ray *ray);
void	set_ray(t_player *player, t_ray *ray, int screen_x);

// select_texture_bonus.c
int		check_dir(t_ray *ray);
void	calculate_texture_x(t_ray *ray);
void	select_texture(t_data *data, t_ray *ray);
void	calculate_wall_x(t_data *data, t_ray *ray);

// set_info_bonus.c
void	set_data(t_data *data);
void	ft_init_buffer(t_data *data);
void	set_player(t_player *player, t_map *map);
void	check_player(t_player *player, t_map *map);

// key_left_right_bonus.c
void	key_left(t_data *data);
void	key_right(t_data *data);

// key_player_bonus.c
void	key_player_w(t_data *data);
void	key_player_s(t_data *data);
void	key_player_a(t_data *data);
void	key_player_d(t_data *data);

#endif