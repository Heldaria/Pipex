/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 04:37:30 by rigel             #+#    #+#             */
/*   Updated: 2022/04/01 20:28:45 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_infile(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], pipex);
	else
	{
		pipex->fdin = open(argv[1], O_RDONLY);
		if (pipex->fdin < 0)
		{
			ft_msg("Failed to open infile.\n");
			return (0);
		}
	}
	return (1);
}

int	get_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->fdout = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->fdout = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->fdout < 0)
	{
		ft_msg("Failed to open outfile.\n");
		return (0);
	}
	return (1);
}

static void	error_heredoc(t_pipex *pipex)
{
	if (pipex->fdin < 0)
	{
		unlink(".heredoc_tmp");
		ft_msg("Error here_doc.\n");
	}
}

void	here_doc(char *argv, t_pipex *pipex)
{
	int			file;
	char		*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		ft_msg("Error here_doc.\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(1, 0);
		if (!buf)
			exit (1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
		{
			free(buf);
			buf = get_next_line(2, 0);
			break ;
		}
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	pipex->fdin = open(".heredoc_tmp", O_RDONLY);
	error_heredoc(pipex);
}
