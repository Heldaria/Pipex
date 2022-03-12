/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 04:37:30 by rigel             #+#    #+#             */
/*   Updated: 2022/03/12 03:32:05 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_infile(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], pipex);
	else
	{
		pipex->fdin = open(argv[1], O_RDONLY);
		if (pipex->fdin < 0)
			ft_msg("Failed to open infile.");
	}
}

void	get_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->fdout = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->fdout = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->fdout < 0)
		ft_msg("Failed to open outfile.");
}

void	here_doc(char *argv, t_pipex *pipex)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		ft_msg("error here_doc");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!buf)
            exit (1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break;
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(file);
	pipex->fdin = open(".heredoc_tmp", O_RDONLY);
	if (pipex->fdin < 0)
	{
		unlink(".heredoc_tmp");
		ft_msg("error here_doc");
	}
}