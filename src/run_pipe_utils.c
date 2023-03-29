/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:24:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/29 20:39:36 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern pid_t	g_pid;

void	close_fd(int fd0, int fd1)
{
	close(fd0);
	close(fd1);
}

void	run_pipe_left(int fd[2], char *line, char *del, t_msh *msh)
{
	g_pid = fork();
	sig_handler(2);
	if (g_pid == -1)
		return (msh->exit_status = 1, perror("fork"));
	else if (g_pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(line, del, msh);
		exit(msh->exit_status);
	}
	waitpid(g_pid, &msh->exit_status, 0);
	msh->exit_status = WEXITSTATUS(msh->exit_status);
}

void	run_pipe_right(int fd[2], char *eline, char *del, t_msh *msh)
{
	g_pid = fork();
	if (g_pid == -1)
		return (perror("fork"), msh->exit_status = 1, close_fd(fd[0], fd[1]));
	else if (g_pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(del + 1, eline, msh);
		exit(msh->exit_status);
	}
	close_fd(fd[0], fd[1]);
	waitpid(g_pid, &msh->exit_status, 0);
	msh->exit_status = WEXITSTATUS(msh->exit_status);
}
