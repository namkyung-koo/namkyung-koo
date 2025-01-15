/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:10:18 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/15 16:42:27 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	msg_and_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	parse_argv(char *argv)
{
	if (!ft_strcmp(argv, "Mandelbrot"))
		return (MANDELBROT);
	else if (!ft_strcmp(argv, "Julia"))
		return (JULIA);
	else if (!ft_strcmp(argv, "Burningship"))
		return (BURNINGSHIP);
	else
		return (INVALID);
	return (INVALID);
}

void	print_valid_list(void)
{
	printf("These are invalided parameters. Please choose below parameters.\n");
	printf("If you want to see Julia set, you can choose real, imag values.\n\n");
	printf("1) Mandelbrot\n");
	printf("2) Julia [real_number] [imaginary_number]\n");
	printf("3) Burningship\n");
	exit(1);
}
