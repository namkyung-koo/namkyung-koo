/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:40 by nakoo             #+#    #+#             */
/*   Updated: 2023/01/25 14:26:07 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../libft/libft.h"

enum e_flag {
	READ,
	WRITE,
	HERE_DOC
};

/* pipex_bonus.c */
int		open_file(char *file, int flag);
void	here_doc(char **av, char **envp, int outfile_fd);

/* utils_bonus.c */
char	**find_path(char **envp);
void	exec(char *av, char **envp);
void	wait_children(int num_of_children);
void	multiple_pipex(int ac, char **av, char **envp);
void	pipex(char **av, char **envp, int *tmp_pipe, int outfile_fd);

#endif