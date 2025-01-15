/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:19:48 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/21 20:20:24 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "structure.h"
# include "keycode.h"
# include "enum.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>

/* window */
# define HEIGHT 500
# define WIDTH 500
# define MAX_ITERATION 150
# define TITLE "fractol"

/* fractal_set.c */
int		mandelbrot(int iter, t_data *data);
int		julia(int iter, t_data *data);
int		burningship(int iter, t_data *data);

/* hooking_key.c */
int		key_hook(int keycode, t_data *data);
int		ft_close(t_data *data);

/* hooking_mouse.c */
int		mouse_hook(int button, int x, int y, t_data *data);
void	mouse_zoom(t_data *data);

/* main.c */
void	initialize_vals(t_data *data);
int		window_init(t_data *data);

/* parsing.c */
int		parse_argv(char *argv);
void	print_valid_list(void);
void	msg_and_exit(char *msg);

/* pixeling.c */
int		color_set(int iter, t_data *data);
void	put_pixel(t_data *data);
void	my_mlx_pixel_put(t_data *data, int color);

/* utils.c */
int		space_and_sign(const char **str, double *res);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
double	ft_atof(const char *str);

/* utils2.c */
void	*ft_memset(void *b, int c, size_t len);

#endif