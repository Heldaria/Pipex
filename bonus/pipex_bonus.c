/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llepiney <llepiney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:10:06 by ayblin            #+#    #+#             */
/*   Updated: 2022/04/01 19:47:10 by llepiney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int	ft_msg(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

static int	args_count(char *arg, t_pipex *pipex)
{
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < args_count(argv[1], &pipex))
		return (ft_msg("Invalid number of arguments.\n"));
	if (!get_infile(argv, &pipex) || !get_outfile(argv[argc - 1], &pipex))
		return (0);
	pipex.idx = -1;
	pipex.cmd_nbs = argc - 3 - pipex.here_doc;
	pipex.path_from_envp = find_path(envp);
	pipex.mypaths = ft_split(pipex.path_from_envp, ':');
	while (++(pipex.idx) < pipex.cmd_nbs)
	{
		if (argv[pipex.idx + 2 + pipex.here_doc][0] == 0)
		{
			parent_free(&pipex);
			return (ft_msg("Invalid arguments.\n"));
		}
		child(pipex, argv, envp);
	}
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
}
