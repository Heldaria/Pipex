/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:10:06 by ayblin            #+#    #+#             */
/*   Updated: 2022/03/03 00:17:54 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
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
	write(2, "\n", 1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	pipex.idx = -1;
	pipex.cmd_nbs = argc - 3;
	pipex.pipe_nbs = (pipex.cmd_nbs - 1) * 2;
	pipex.pipe_fd = malloc(sizeof(int) * 2);
	if (!pipex.pipe_fd)
		return(ft_msg("Failed to malloc pipe"));
	if (pipe(pipex.pipe_fd) < 0)
		return(-1);
	pipex.fdin = open(argv[1], O_RDONLY);
	pipex.fdout = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.fdin < 0 || pipex.fdout < 0)
		return (ft_msg("Failed to open infile or outfile."));
	pipex.path_from_envp = find_path(envp);
	pipex.mypaths = ft_split(pipex.path_from_envp, ':');
	while (++(pipex.idx) < pipex.cmd_nbs)
	{
		//printf("idx :%d \n ",pipex.idx);
		child(pipex, argv, envp);
	}
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
}
