/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 03:15:20 by rigel             #+#    #+#             */
/*   Updated: 2022/04/01 14:45:38 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = ft_strjoin(path, "/");
	command = ft_strjoin(tmp, cmd);
	free(tmp);
	return (command);
}

void	child_process1(t_pipex pipex, char **argv, char **envp)
{
	int		i;

	pipex.mycmdargs = ft_split(argv[2], ' ');
	i = 0;
	dup2(pipex.fdin, STDIN_FILENO);
	dup2(pipex.tube[1], STDOUT_FILENO);
	close(pipex.tube[0]);
	while (pipex.mypaths[i])
	{
		pipex.cmd = get_cmd(pipex.mypaths[i], pipex.mycmdargs[0]);
		execve(pipex.cmd, pipex.mycmdargs, envp);
		i++;
	}
	child_free(&pipex);
	write(2, "Command not found.\n", 18);
}

void	child_process2(t_pipex pipex, char **argv, char **envp)
{
	int		i;

	pipex.mycmdargs = ft_split(argv[3], ' ');
	i = 0;
	waitpid(pipex.pid1, NULL, 0);
	dup2(pipex.tube[0], STDIN_FILENO);
	dup2(pipex.fdout, STDOUT_FILENO);
	close(pipex.tube[1]);
	while (pipex.mypaths[i])
	{
		pipex.cmd = get_cmd(pipex.mypaths[i], pipex.mycmdargs[0]);
		execve(pipex.cmd, pipex.mycmdargs, envp);
		i++;
	}
	child_free(&pipex);
	write(2, "Command not found.\n", 18);
}
