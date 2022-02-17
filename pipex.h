/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 09:29:29 by rigel             #+#    #+#             */
/*   Updated: 2022/02/08 01:50:34 by rigel            ###   ########.fr       */
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
# include <stdlib.h>

char	    *find_path(char **envp);
int         pipex(int   fdin, int fdout,char **argv,char **envp);
int         ft_strncmp(const char *s1, const char *s2, size_t n);
char        **ft_split(char const *s, char c);
char        *ft_strjoin(char const *s1, char const *s2);
char        *get_cmd(char *path, char *cmd);
int         child_process1(int fdin, char **mypaths, char **argv,int *fd,char **envp);
int         child_process2(int fdout, char **mypaths, char **argv,int *fd, char **envp, int pid1);
char        *ft_substr(char const *s, unsigned int start, size_t len);

#endif