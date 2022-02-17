/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 01:39:50 by rigel             #+#    #+#             */
/*   Updated: 2022/02/08 01:36:35 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    int fdin;
    int fdout;

    if(argc != 5)
        return 1;
    fdin = open(argv[1], O_RDONLY);
    fdout = open(argv[4],O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fdin < 0 || fdout < 0)
        return 1;
    pipex(fdin,fdout,argv,envp);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int pipex(int   fdin, int fdout,char **argv,char **envp)
{
    int fd[2];
    char *PATH_from_envp;
    char **mypaths;

    PATH_from_envp = find_path(envp);
    mypaths = ft_split(PATH_from_envp, ":"); 
    pipe(fd);
    int pid1 = fork();
    if (pid1 < 0)
        return 1;
    if (pid1 == 0)
        child_process1(fdin, mypaths, argv, fd, envp);
    int pid2 = fork();
    if (pid2 < 0)
        return 1;
    if (pid2 == 0)
        child_process2(fdout, mypaths, argv, fd, envp,pid1); 
}
