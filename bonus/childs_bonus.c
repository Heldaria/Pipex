/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:34:18 by rigel             #+#    #+#             */
/*   Updated: 2022/03/03 00:25:26 by rigel            ###   ########.fr       */
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
/*
static void	ft_printab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_msg(tab[i]);
		i++;
	}
}*/

int    child(t_pipex p, char **argv, char **envp)
{
    int 	i;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return(-1);
    if (pid == 0)
	{
		if (p.idx == (p.cmd_nbs - 1))
		{
			dup2(p.fdout, 1);
		//	close(p.pipe_fd[1]);
		//	close(p.pipe_fd[0]);
		}
		else
		{
			dup2(p.pipe_fd[1], 1);
		//	close(p.pipe_fd[0]);
		}
		if (p.idx == 0)
		{
			dup2(p.fdin, 0);
		//	close(p.pipe_fd[1]);
		//	close(p.pipe_fd[0]);
		}
		close(p.pipe_fd[1]);
		close(p.pipe_fd[0]);
	}
    else
	{
		dup2(p.pipe_fd[0], 0);
		close(p.pipe_fd[1]);
	//	close(p.pipe_fd[0]);
	}
	//ft_printab(p.mypaths);
	i = 0;
	if (pid == 0)
	{
		p.mycmdargs = ft_split(argv[p.idx + 2], ' ');
		//ft_printab(p.mycmdargs);
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