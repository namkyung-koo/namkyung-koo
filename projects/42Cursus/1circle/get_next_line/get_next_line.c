/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:03:38 by nakoo             #+#    #+#             */
/*   Updated: 2022/11/01 09:07:14 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_memory(char **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*update_backup(char **backup, char *buff)
{
	char	*new_backup;
	size_t	backup_len;
	size_t	buff_len;

	if (*backup == NULL)
		*backup = (char *)ft_calloc(1, 1);
	backup_len = ft_strlen(*backup);
	buff_len = ft_strlen(buff);
	new_backup = (char *)ft_calloc(backup_len + buff_len + 1, 1);
	if (!new_backup)
		return (free_memory(backup));
	ft_strlcat(new_backup, *backup, backup_len + buff_len + 1);
	ft_strlcat(new_backup, buff, backup_len + buff_len + 1);
	free_memory(backup);
	return (new_backup);
}

char	*make_line_with_newline_or_null(char **backup)
{
	char	*nl_or_null;
	char	*ret;
	char	*new_backup;
	size_t	backup_len;

	if (ft_strchr(*backup, '\n'))
		nl_or_null = ft_strchr(*backup, '\n') + 1;
	else
		nl_or_null = ft_strchr(*backup, '\0');
	backup_len = ft_strlen(*backup);
	ret = (char *)ft_calloc(nl_or_null - *backup + 1, 1);
	if (!ret)
		return (free_memory(backup));
	ft_strlcat(ret, *backup, nl_or_null - *backup + 1);
	new_backup = (char *)ft_calloc((*backup + backup_len) - nl_or_null + 1, 1);
	if (!new_backup)
		return (free_memory(backup));
	ft_strlcat(new_backup, nl_or_null, (*backup + backup_len) - nl_or_null + 1);
	free_memory(backup);
	*backup = new_backup;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		buff[(BUFFER_SIZE) + 1];
	char		*ret;
	ssize_t		bytes;

	if (fd < 0 || (BUFFER_SIZE) <= 0)
		return (NULL);
	while (!ft_strchr(backup, '\n'))
	{
		bytes = read(fd, buff, (BUFFER_SIZE));
		if (bytes == -1 || buff[0] == '\0')
			return (free_memory(&backup));
		buff[bytes] = '\0';
		backup = update_backup(&backup, &buff[0]);
		if (bytes == 0)
			break ;
	}
	if (bytes == 0 && *backup == '\0')
		return (free_memory(&backup));
	if (ft_strchr(backup, '\n'))
		return (make_line_with_newline_or_null(&backup));
	ret = make_line_with_newline_or_null(&backup);
	free_memory(&backup);
	return (ret);
}
