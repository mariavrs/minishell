/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 19:24:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/03 01:41:52 by mvorslov         ###   ########.fr       */
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

static void	run_pipe_left(t_pp *pipe_info, char *line, char *del, t_msh *msh)
{
	pipe_info->pid[0] = fork();
	if (pipe_info->pid[0] == -1)
		return (g_exit_status = 1, perror("minishell"));
	else if (pipe_info->pid[0] == 0)
	{
		msh->out_pipe_flag = 1;
		dup2(pipe_info->fd[1], STDOUT_FILENO);
		close_pipe_fd(pipe_info->fd[0], pipe_info->fd[1]);
		parse_pipe(line, del, msh);
		ft_free_exit(msh);
		exit(g_exit_status);
	}
}

static void	run_pipe_right(t_pp *pipe_info, char *eline, char *del, t_msh *msh)
{
	pipe_info->pid[1] = fork();
	if (pipe_info->pid[1] == -1)
		return (perror("minishell"), g_exit_status = 1,
			close_pipe_fd(pipe_info->fd[0], pipe_info->fd[1]));
	else if (pipe_info->pid[1] == 0)
	{
		msh->in_pipe_flag = 1;
		dup2(pipe_info->fd[0], STDIN_FILENO);
		close_pipe_fd(pipe_info->fd[0], pipe_info->fd[1]);
		parse_pipe(del + 1, eline, msh);
		ft_free_exit(msh);
		exit(g_exit_status);
	}
	close_pipe_fd(pipe_info->fd[0], pipe_info->fd[1]);
	waitpid(pipe_info->pid[0], &pipe_info->status[0], 0);
	g_exit_status = WEXITSTATUS(pipe_info->status[0]);
	waitpid(pipe_info->pid[1], &pipe_info->status[1], 0);
	g_exit_status = WEXITSTATUS(pipe_info->status[1]);
}

void	run_pipe(char *line, char *eline, char *del, t_msh *msh)
{
	t_pp	pipe_info;

	pipe(pipe_info.fd);
	if (pipe(pipe_info.fd) == -1)
		return (perror("minishell"));
	run_pipe_left(&pipe_info, line, del, msh);
	if (!g_exit_status)
		run_pipe_right(&pipe_info, eline, del, msh);
	else
		close_pipe_fd(pipe_info.fd[0], pipe_info.fd[1]);
}
