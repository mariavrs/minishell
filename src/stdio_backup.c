/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_backup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 01:53:16 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/13 02:05:57 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	get_backup_stdio(t_msh *msh, t_cmd *cmd)
{
	if (msh->pipe_flag)
		return ;
	if (cmd->rdr_in_flag)
	{
		cmd->stdin_backup = dup(STDIN_FILENO);
		if (cmd->stdin_backup == -1)
			return (perror("minishell"), ft_putendl_fd("I/O backup failed", 2),
				ft_exit_error(0, NULL, msh, ERR_IO));
	}
	if (cmd->rdr_out_flag)
	{
		cmd->stdout_backup = dup(STDOUT_FILENO);
		if (cmd->stdout_backup == -1)
		{
			if (cmd->stdin_backup >= 0)
				close(cmd->stdin_backup);
			return (perror("minishell"), ft_putendl_fd("I/O backup failed", 2),
				ft_exit_error(0, NULL, msh, ERR_IO));
		}
	}
}

static int	backup_dup_back(int fd_backup, int fd_stdio, int io_flag)
{
	int	status;

	status = dup2(fd_backup, fd_stdio);
	close(fd_backup);
	if (status != -1)
		return (0);
	ft_putstr_fd("minishell: ", 2);
	if (!io_flag)
		perror("STDIN");
	else if (io_flag == 1)
		perror("STDOUT");
	close(fd_stdio);
	return (1);
}

void	put_backup_stdio(t_msh *msh, t_cmd *cmd)
{
	int	status;

	status = 0;
	if (msh->pipe_flag)
		return ;
	if (cmd->rdr_in_flag)
		status += backup_dup_back(cmd->stdin_backup, STDIN_FILENO, 0);
	if (cmd->rdr_out_flag)
		status += backup_dup_back(cmd->stdout_backup, STDOUT_FILENO, 1);
	if (status > 0)
	{
		ft_putendl_fd("STD I/O could not be restored", 2);
		ft_exit_error(0, NULL, msh, ERR_IO);
	}
}
