/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:37:53 by nakoo             #+#    #+#             */
/*   Updated: 2023/01/20 19:44:58 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_children(int num_of_children)
{
	int	i;

	i = 0;
	while (i < num_of_children)
	{
		ft_assert(waitpid(-1, NULL, 0) != -1, "waitpid error" );
		i++;
	}
}

char	**find_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(envp[i] + 5, ':');
	ft_assert((path != NULL), "Failed to execute ft_split ");
	return (path);
}

void	exec(char *av, char **envp)
{
	char	**path;
	char	**opt;
	char	*cmd;
	int		i;

	opt = ft_split(av, ' ');
	ft_assert((opt != NULL), "Failed to execute ft_split ");
	path = find_path(envp);
	i = 0;
	while (path[i] != NULL)
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, opt[0]);
		if (access(cmd, X_OK) == 0)
			break ;
		i++;
	}
	if (access(cmd, X_OK) == -1)
		ft_assert(FALSE, "Failed to execute access ");
	ft_assert(!(execve(cmd, opt, envp) == -1), "Failed to execute execve ");
}

void	multiple_pipex(int ac, char **av, char **envp)
{
	int		old_fd[2];
	int		new_fd[2];
	int		cmd;
	pid_t	pid;

	cmd = 2;
	old_fd[0] = STDIN_FILENO;
	while (cmd < ac - 2)
	{
		pipe(new_fd);
		pid = fork();
		if (pid == 0)
		{
			close(new_fd[0]);
			dup2(old_fd[0], STDIN_FILENO);
			dup2(new_fd[1], STDOUT_FILENO);
			exec(av[cmd], envp);
		}
		close(old_fd[0]);
		close(new_fd[1]);
		ft_memcpy(old_fd, new_fd, sizeof(int) * 2);
		cmd++;
	}
	dup2(old_fd[0], STDIN_FILENO);
	exec(av[ac - 2], envp);
}

void	pipex(char **av, char **envp, int *tmp_pipe, int outfile_fd)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(tmp_pipe[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(tmp_pipe[0]);
		exec(av[3], envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(fd[1]);
		exec(av[4], envp);
	}
	close(fd[0]);
	close(fd[1]);
	wait_children(2);
}
