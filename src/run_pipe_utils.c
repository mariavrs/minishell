/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:24:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/31 14:15:08 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	close_fd(int fd0, int fd1)
{
	close(fd0);
	close(fd1);
}

void	run_pipe_left(int fd[2], char *line, char *del, t_msh *msh)
{
	pid_t	id;

	id = fork();
	signal_manager(2);
	if (id == -1)
		return (g_exit_status = 1, perror("minishell"));
	else if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(line, del, msh);
		exit(g_exit_status);
	}
	waitpid(id, &g_exit_status, 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
}

void	run_pipe_right(int fd[2], char *eline, char *del, t_msh *msh)
{
	pid_t	id;

	id = fork();
	signal_manager(2);
	if (id == -1)
		return (perror("minishell"), g_exit_status = 1, close_fd(fd[0], fd[1]));
	else if (id == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close_fd(fd[0], fd[1]);
		parse_pipe(del + 1, eline, msh);
		exit(g_exit_status);
	}
	close_fd(fd[0], fd[1]);
	waitpid(id, &g_exit_status, 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
}
