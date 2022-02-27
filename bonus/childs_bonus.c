/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:34:18 by rigel             #+#    #+#             */
/*   Updated: 2022/02/27 19:41:27 by rigel            ###   ########.fr       */
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

static void	sub_dup2(int zero, int one)
{
	dup2(zero, 0);
	dup2(one, 1);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nbs))
	{
		close(pipex->tube[i]);
		i++;
	}
}

void	close_pipes_idx(t_pipex *p, int idx)
{
	int	i;

	i = 0;
	while (i < (p->pipe_nbs))
	{
		if (idx == 0)
		{
			if (i == 1)
				i++;
		}
		else if (idx == p->cmd_nbs - 1)
		{
			if (i == (2 * idx -2))
				i++;
		}
		if (i == (2 * idx - 2) || i == (2 * idx + 1))
			i++;
		else
		{
			close(p->tube[i]);
			i++;
		}
	}
}

/*void	close_pipes_after(t_pipex *p, int idx)
{
	if (idx == 0)
		close(p->tube[1]);
	else if (idx == p->cmd_nbs - 1)
		close(p->tube[])
}
*/

void    child(t_pipex p, char **argv, char **envp)
{
    int i;

    i = 0;
    p.pid = fork();
    if (p.pid == 0)
    {
        if (p.idx == 0)
            sub_dup2(p.fdin, p.tube[1]);
        else if (p.idx == (p.cmd_nbs - 1))
           sub_dup2(p.tube[2 * p.idx - 2], p.fdout);
        else
            sub_dup2(p.tube[2 * p.idx - 2], p.tube[2 * p.idx + 1]);
        p.mycmdargs = ft_split(argv[3], ' ');
		close_pipes(&p);
        while (p.mypaths[i])
	    {
		    p.cmd = get_cmd(p.mypaths[i], p.mycmdargs[0]);
		    execve(p.cmd, p.mycmdargs, envp);
		    i++;
	    }
	    child_free(&p);
	    write(2, "Command not found.\n", 19);
    }
}