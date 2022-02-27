/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:29:29 by ayblin            #+#    #+#             */
/*   Updated: 2022/02/26 14:45:41 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		pid1;
	int		pid2;
	int		tube[2];
	int		fdin;
	int		fdout;
	char	*paths;
	char	**mypaths;
	char	*path_from_envp;
	char	*cmd;
	char	**mycmdargs;
}t_pipex;

char		*find_path(char **envp);
int			pipex(t_pipex pipex, char **argv, char **envp);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*get_cmd(char *path, char *cmd);
void		child_process1(t_pipex pipex, char **argv, char **envp);
void		child_process2(t_pipex pipex, char **argv, char **envp);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_msg(char *str);
int			ft_strlen(char *str);
void		parent_free(t_pipex *pipex);
void		child_free(t_pipex *pipex);
#endif