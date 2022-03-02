/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:29:29 by ayblin            #+#    #+#             */
/*   Updated: 2022/03/02 23:47:32 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>

typedef struct s_pipex
{
	int		cmd_nbs;
	int		pipe_nbs;
	int		fdin;
	int		*pipe_fd;
	int		idx; 
	char	*paths;
	int		fdout; 
	char	**mypaths;
	char	*path_from_envp;
	char	*cmd;
	char	**mycmdargs;
}t_pipex;

int		child(t_pipex p, char **argv, char **envp);
char	*find_path(char **envp);
int		ft_strlen(char *str);
int		ft_msg(char *str);
char	**ft_split(char const *s, char c);
void	child_free(t_pipex *pipex);
void	parent_free(t_pipex *pipex);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif