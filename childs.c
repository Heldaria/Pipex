/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rigel <rigel@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 03:15:20 by rigel             #+#    #+#             */
/*   Updated: 2022/02/08 01:51:28 by rigel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd(char *path, char *cmd)
{
    char    *tmp;
    char    *command;

    tmp = ft_strjoin(path,'/');
    command = ft_strjoin(tmp,cmd);
    free(tmp);
    return (command);
}

int    child_process1(int fdin, char **mypaths, char **argv,int *fd,char **envp)
{
    int i;
    char *cmd;
    char    **mycmdargs;

    mycmdargs = ft_split(argv[2], ' ');
    i = 0;
    dup2(fdin,STDIN_FILENO);
    dup2(fd[1],STDOUT_FILENO);
    close(fd[0]);
    close(fdin);
    while (mypaths[i])
    {
        cmd = get_cmd(mypaths[i],mycmdargs[0]);
        execve(cmd, mycmdargs, envp);
        i++;
    }
    
}

int   child_process2(int fdout, char **mypaths, char **argv,int *fd, char **envp, int pid1)
{
    int i;
    char    *cmd;
    char    **mycmdargs;

    mycmdargs = ft_split(argv[3], ' ');
    i = 0;
    waitpid(pid1,NULL,0);
    dup2(fd[0],STDIN_FILENO);
    dup2(fdout,STDOUT_FILENO);
    close(fd[1]);
    close(fdout);
  while (mypaths[i])
    {
        cmd = get_cmd(mypaths[i],mycmdargs[0]);
        execve(cmd, mycmdargs, envp);
        i++;
    }
}


