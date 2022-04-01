/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 01:39:50 by rigel             #+#    #+#             */
/*   Updated: 2022/02/26 14:45:44 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_msg(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		return (ft_msg("invalid number of arguments"));
	pipex.fdin = open(argv[1], O_RDONLY);
	pipex.fdout = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.fdin < 0 || pipex.fdout < 0)
		return (ft_msg("failed to open infile or outfile"));
	pipex.path_from_envp = find_path(envp);
	pipex.mypaths = ft_split(pipex.path_from_envp, ':');
	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 < 0)
		return (1);
	if (pipex.pid1 == 0)
		child_process1(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		return (1);
	if (pipex.pid2 == 0)
		child_process2(pipex, argv, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}
