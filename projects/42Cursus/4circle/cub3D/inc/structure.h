/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisulee <jisulee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:18:29 by nakoo             #+#    #+#             */
/*   Updated: 2023/07/07 22:28:13 by jisulee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "../libft/libft.h"

typedef struct s_ray {
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		start_point;
	int		end_point;
	int		tex_num;
	double	wall_x;
	int		texture_x;
}	t_ray;

typedef struct s_image {
	void	*img;
	int		*img_data;
	int		img_width;
	int		img_height;
	int		size;
	int		bpp;
	int		endian;
}	t_image;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_flag {
	int		is_north_texture;
	int		is_south_texture;
	int		is_west_texture;
	int		is_east_texture;
	int		is_floor;
	int		is_ceiling;
	int		over_identifier;
	int		is_map;
}	t_flag;

typedef struct s_map {
	int		player;
	int		player_x;
	int		player_y;
	int		view_dir;
	int		width;
	int		height;
	int		**frame;
	char	**arr;
	t_list	*list;
}	t_map;

typedef struct s_data {
	void		*mlx;
	void		*win;
	char		*no_texture_path;
	char		*so_texture_path;
	char		*we_texture_path;
	char		*ea_texture_path;
	int			floor_rgb;
	int			ceiling_rgb;
	int			**texture;
	int			**buffer;
	t_map		map;
	t_flag		flag;
	t_player	player;
	t_image		screen_img;
	t_ray		ray;
}	t_data;

#endif