/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:24:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/09 08:09:33 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

typedef struct s_pipe
{
	int	fd[2];
	int	pid[2];
	int	status[2];
}	t_pp;

static void	close_pipe_fd(int fd0, int fd1)
{
	close(fd0);
	close(fd1);
}

static int	run_pipe_next(t_msh *msh, t_cmd *cmd, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close_pipe_fd(fd[0], fd[1]);
	if (cmd->next)
		run_pipe_new(msh, cmd);
	else
	{
		run_cmd_exec(msh, cmd);
		close_pipe_fd(STDIN_FILENO, STDOUT_FILENO);
		return (ft_free_exit(msh), g_exit_status);
	}
	return (g_exit_status);
}

void	run_pipe_new(t_msh *msh, t_cmd *cmd)
{
	int	fd[2];
	int	pid;

	pipe(fd);
	if (pipe(fd) == -1)
		return (g_exit_status = 1, perror("minishell"));
	pid = fork();
	if (pid == 0)
		exit(run_pipe_next(msh, cmd->next, fd));
	dup2(fd[1], STDOUT_FILENO);
	close_pipe_fd(fd[0], fd[1]);
	run_cmd_exec(msh, cmd);
	close_pipe_fd(STDIN_FILENO, STDOUT_FILENO);
	ft_free_exit(msh);
	waitpid(pid, &g_exit_status, 0);
	g_exit_status = WEXITSTATUS(g_exit_status);
	exit(g_exit_status);
}
