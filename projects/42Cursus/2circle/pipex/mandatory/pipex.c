/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakoo <nakoo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:51:11 by nakoo             #+#    #+#             */
/*   Updated: 2023/01/25 14:14:11 by nakoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	pipex(char **av, char **envp, int infile_fd, int outfile_fd)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(infile_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		exec(av[2], envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(outfile_fd, STDOUT_FILENO);
		close(fd[1]);
		exec(av[3], envp);
	}
	close(fd[0]);
	close(fd[1]);
	ft_assert(waitpid(-1, NULL, 0) != -1, "waitpid error ");
	ft_assert(waitpid(-1, NULL, 0) != -1, "waitpid error ");
}

int	main(int ac, char **av, char **envp)
{
	int	infile_fd;
	int	outfile_fd;

	ft_assert((ac == 5), "./pipex infile cmd1 cmd2 outfile ");
	infile_fd = open(av[1], O_RDONLY);
	outfile_fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_assert(!(infile_fd < 0 || outfile_fd < 0), "Failed to open files ");
	pipex(av, envp, infile_fd, outfile_fd);
	return (0);
}
