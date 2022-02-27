/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:22:29 by ayblin            #+#    #+#             */
/*   Updated: 2022/02/26 16:01:39 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->mycmdargs[i])
	{
		free(pipex->mycmdargs[i]);
		i++;
	}
	free(pipex->mycmdargs);
	free(pipex->cmd);
}

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->fdin);
	close(pipex->fdout);
	while (pipex->mypaths[i])
	{
		free(pipex->mypaths[i]);
		i++;
	}
	free(pipex->mypaths);
}
