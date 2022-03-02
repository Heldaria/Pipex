/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:34:18 by rigel             #+#    #+#             */
/*   Updated: 2022/03/02 13:59:56 by rigel            ###   ########.fr       */
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

int    child(t_pipex p, char **argv, char **envp)
{
    int 	i;
	pid_t	pid;
	int		pipe_fd[2];

    i = 0;
	pid = fork();
	if (pid == -1)
		return(-1);
	if (pipe(pipe_fd) < 0)
		return(-1);
    if (pid == 0)
	{
	   dup2(pipe_fd[1], 1);
	   close(pipe_fd[0]);
	   close(pipe_fd[1]);
	}
    else
	{
        dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
    p.mycmdargs = ft_split(argv[p.idx + 2], ' ');
	if (pid == 0)
	{
        while (p.mypaths[i])
	    {
		    p.cmd = get_cmd(p.mypaths[i], p.mycmdargs[0]);
			ft_msg(p.cmd);
		    execve(p.cmd, p.mycmdargs, envp);
		    i++;
	    }
	    child_free(&p);
	    write(2, "Command not found.\n", 19);
    }
	return (0);
}