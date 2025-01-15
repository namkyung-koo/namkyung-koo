/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:45:38 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/17 15:57:58 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_img
{
	double	julia_real;
	double	julia_imag;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		set;
	int		rgb;
}	t_img;

typedef struct s_vals
{
	double	set_height;
	double	set_width;
	double	mouse_x;
	double	mouse_y;
	double	bottom;
	double	right;
	double	left;
	double	top;
	double	mv_x;
	double	mv_y;
	double	zoom;
	int		count_w;
	int		count_h;
}	t_vals;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_vals	vals;
}	t_data;

#endif