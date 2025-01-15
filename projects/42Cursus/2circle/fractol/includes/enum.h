/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:44:24 by nakoo             #+#    #+#             */
/*   Updated: 2022/12/17 14:48:46 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum e_status {
	INVALID = -1,
	MANDELBROT,
	JULIA,
	BURNINGSHIP
};

enum e_boolean {
	FALSE,
	TRUE
};

enum e_color {
	CHANGE_R = 1,
	CHANGE_G = 2,
	CHANGE_B = 4,
	CHANGE_ALL = 8
};

#endif