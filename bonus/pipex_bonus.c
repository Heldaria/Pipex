/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:10:06 by ayblin            #+#    #+#             */
/*   Updated: 2022/02/27 19:15:23 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nbs - 1)
	{
		if (pipe(pipex->tube + 2 * i) < 0)
			parent_free(pipex);
		i++;
	}
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
	write(2, str, ft_strlen(str));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.idx = -1;
	pipex.cmd_nbs = argc - 3;
	pipex.pipe_nbs = (pipex.cmd_nbs - 1) * 2;
	pipex.tube = (int *)malloc(sizeof(int) * pipex.pipe_nbs);
	if (!pipex.tube)
		return (ft_msg("malloc error (pipe)"));
	pipex.fdin = open(argv[1], O_RDONLY);
	pipex.fdout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.fdin < 0 || pipex.fdout < 0)
		return (ft_msg("failed to open infile or outfile"));
	pipex.path_from_envp = find_path(envp);
	pipex.mypaths = ft_split(pipex.path_from_envp, ':');
	create_pipes(&pipex);
	while (++(pipex.idx) < pipex.cmd_nbs)
	{
		printf("idx :%d \n ",pipex.idx);
		child(pipex, argv, envp);
	}
	waitpid(-1, NULL, 0);
	close_pipes(&pipex);
	parent_free(&pipex);
}