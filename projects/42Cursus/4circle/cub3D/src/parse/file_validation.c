/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:23:58 by nakoo             #+#    #+#             */
/*   Updated: 2023/06/30 20:15:08 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_empty_file(const char *cub_file)
{
	char	temp[2];
	int		byte;
	int		fd;

	temp[0] = '\0';
	fd = open(cub_file, O_RDONLY);
	byte = read(fd, temp, 1);
	if (byte == 0)
	{
		close(fd);
		error_and_exit("The cub file is empty.");
	}
	close(fd);
}

static int	manipulate_line(t_data *data, char *line)
{
	if (data->flag.over_identifier == FALSE)
		skip_space(&line);
	if ((*line) == '\0')
		return (0);
	if (data->flag.over_identifier == FALSE && \
	(ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
	|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 \
	|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0))
		return (fill_identifier(data, line));
	else if (data->flag.over_identifier == TRUE && \
	ft_strncmp(line, "NO ", 3) != 0 && ft_strncmp(line, "SO ", 3) != 0 \
	&& ft_strncmp(line, "WE ", 3) != 0 && ft_strncmp(line, "EA ", 3) != 0 \
	&& ft_strncmp(line, "F ", 2) != 0 && ft_strncmp(line, "C ", 2) != 0)
		return (fill_map(data, line));
	return (-1);
}

static int	read_cub_file(int fd, t_data *data)
{
	char	*line;
	char	*temp;

	while (42)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = line;
		newline_to_null(temp);
		if (manipulate_line(data, temp) == -1)
			return \
			(print_error("The file's format entered wrongly.", -1, line));
		free(line);
	}
	return (0);
}

int	open_cub_file(const char *cub_file, t_data *data)
{
	int	fd;

	is_empty_file(cub_file);
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open CUB FILE", -1, NULL));
	init_t_data(data);
	if (read_cub_file(fd, data) == -1)
	{
		close(fd);
		return (-1);
	}
	check_map_data(data);
	fd = close(fd);
	if (fd == -1)
		return (print_error("Failed to close CUB FILE", -1, NULL));
	return (0);
}
