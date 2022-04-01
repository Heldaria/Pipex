/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:34:18 by rigel             #+#    #+#             */
/*   Updated: 2022/03/12 22:56:59 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = ft_strjoin(path, "/");
	command = ft_strjoin(tmp, cmd);
	free(tmp);
	return (command);
}

static void	ft_fds(t_pipex p, pid_t pid, int *pipe_fd)
{
	if (pid == 0)
	{
		if (p.idx == (p.cmd_nbs - 1))
			dup2(p.fdout, 1);
		else
		{
			if (p.idx == 0)
				dup2(p.fdin, 0);
			dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}
	}
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

int	child(t_pipex p, char **argv, char **envp)
{
	int		i;
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	ft_fds(p, pid, pipe_fd);
	i = 0;
	if (pid == 0)
	{
		p.mycmdargs = ft_split(argv[p.idx + 2 + p.here_doc], ' ');
		while (p.mypaths[i])
		{
			p.cmd = get_cmd(p.mypaths[i], p.mycmdargs[0]);
			execve(p.cmd, p.mycmdargs, envp);
			i++;
		}
		child_free(&p);
		write(2, "Command not found.\n", 19);
	}
	return (0);
}
