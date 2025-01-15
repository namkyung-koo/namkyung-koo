/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:04:05 by nakoo             #+#    #+#             */
/*   Updated: 2023/02/21 15:55:17 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/includes/libft.h"
# include "minishell.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define FALSE 0
# define TRUE 1

# define NL 0
# define NO_NL 1

# define NO_EQUAL 0
# define EQUAL 1

int		ft_export(char **token, char **dup_env);
int		ft_unset(char **token, char **env);
int		ft_cd(char **token, char **env);
int		ft_echo(char **token);
int		ft_exit(char **token);
int		ft_pwd(char **env);
int		ft_env(char **env);

/* builtin_utils.c */
int		error_msg(int expression, char *msg);
void	swap(int *a, int *b);

#endif