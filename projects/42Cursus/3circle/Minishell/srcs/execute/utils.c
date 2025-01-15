/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euiclee <euiclee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:52:17 by euiclee           #+#    #+#             */
/*   Updated: 2023/02/27 08:34:24 by euiclee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	wait_children(int num_of_children)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_of_children)
	{
		ft_assert(waitpid(-1, &status, 0) != -1, "waitpid error", 1);
		i++;
	}
	if (WIFSIGNALED(status))
		g_exit = WTERMSIG(status) + 128;
	else
		g_exit = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGINT)
		write(1, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT)
		write (1, "Quit :3\n", 8);
}

char	**find_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	if (ft_strfind(envp, "PATH") == NULL)
		return (NULL);
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	ft_assert((path != NULL), "Failed to execute ft_split ", 1);
	return (path);
}

void	exec(char **token, char **envp)
{
	char	**path;
	char	*cmd;
	int		i;

	setting_signal(CHILD_EXECVE);
	path = find_path(envp);
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, token[0]);
		if (access(cmd, X_OK) == 0)
			break ;
		i++;
	}
	if (access(cmd, X_OK) == -1 && access(token[0], X_OK) == -1)
		ft_assert(FALSE, "Failed to execute access ", 127);
	if (execve(cmd, token, envp) == -1)
		ft_assert(!(execve(token[0], token, envp) == -1),
			"Failed to execute execve ", 126);
}

int	open_file(char *file, int flag)
{
	int	fd;

	fd = 0;
	if (flag == READ)
		fd = open(file, O_RDONLY);
	else if (flag == WRITE)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == HERE_DOC)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	ft_assert(!(fd < 0), "Failed to open files ", 1);
	return (fd);
}
