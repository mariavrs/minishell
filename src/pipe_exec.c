/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:24:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/13 02:46:11 by mvorslov         ###   ########.fr       */
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

static void	pipe_clean(t_msh *msh, int fd[2], int fd_pipe_flag)
{
	if (fd_pipe_flag)
		close_pipe_fd(fd[0], fd[1]);
	close_pipe_fd(STDIN_FILENO, STDOUT_FILENO);
	ft_free_exit(msh);
}

static int	run_pipe_next(t_msh *msh, t_cmd *cmd, int fd[2])
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (pipe_clean(msh, fd, 1), perror("minishell: pipe"), ERR_PIPE);
	close_pipe_fd(fd[0], fd[1]);
	if (cmd->next)
		run_pipe(msh, cmd);
	else
	{
		run_cmd_exec(msh, cmd);
		if (cmd->error_msg)
			ft_putendl_fd(cmd->error_msg, 2);
		pipe_clean(msh, fd, 0);
		return (g_exit_status);
	}
	return (g_exit_status);
}

static void	pipe_finish(t_msh *msh, t_cmd *cmd, pid_t pid)
{
	close_pipe_fd(STDIN_FILENO, STDOUT_FILENO);
	g_exit_status = waitpid_collect_status(pid);
	if (cmd->error_msg)
		ft_putendl_fd(cmd->error_msg, 2);
	ft_free_exit(msh);
}

void	run_pipe(t_msh *msh, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	if (pipe(fd) == -1)
		return (g_exit_status = ERR_PIPE, perror("minishell: pipe"),
			pipe_clean(msh, fd, 0));
	pid = fork();
	if (pid == -1)
		return (g_exit_status = ERR_PIPE, perror("minishell: fork pipe"),
			pipe_clean(msh, fd, 1));
	if (pid == 0)
		exit(run_pipe_next(msh, cmd->next, fd));
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: pipe");
		g_exit_status = ERR_PIPE;
	}
	close_pipe_fd(fd[0], fd[1]);
	if (g_exit_status != ERR_PIPE)
		run_cmd_exec(msh, cmd);
	pipe_finish(msh, cmd, pid);
	exit(g_exit_status);
}
