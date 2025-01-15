/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:19:04 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/01 09:06:31 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define OPEN_MAX 10240
# define BUFFER_SIZE 8

char	*get_next_line(int fd);
char	*free_memory(char **ptr);
char	*update_backup(char **backup, char *buff);
char	*make_line_with_newline_or_null(char **backup);

#endif