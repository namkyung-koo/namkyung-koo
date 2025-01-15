/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:32 by nakoo             #+#    #+#             */
/*   Updated: 2023/01/25 14:26:36 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file, int flag)
{
	int	fd;

	if (flag == READ)
		fd = open(file, O_RDONLY);
	else if (flag == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_assert(!(fd < 0), "Failed to open files " );
	return (fd);
}

void	here_doc(char **av, char **envp, int outfile_fd)
{
	char	*limiter;
	char	*line;
	int		fd[2];

	limiter = ft_strjoin(av[2], "\n");
	pipe(fd);
	while (TRUE)
	{
		write (STDIN_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strcmp(line, limiter) == 0)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	free(limiter);
	close(fd[1]);
	pipex(av, envp, fd, outfile_fd);
}

int	main(int ac, char **av, char **envp)
{
	int	infiled_fd;
	int	outfile_fd;

	ft_assert(!(ac < 5), "./pipex infile cmd1 cmd2 cmd3 .. cmdn outfile\
	\n./pipex here_doc LIMITER cmd1 cmd2 outfile ");
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		outfile_fd = open_file(av[5], HERE_DOC);
		here_doc(av, envp, outfile_fd);
	}
	else
	{
		infiled_fd = open_file(av[1], READ);
		outfile_fd = open_file(av[ac - 1], WRITE);
		dup2(infiled_fd, STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		multiple_pipex(ac, av, envp);
	}
	return (0);
}
