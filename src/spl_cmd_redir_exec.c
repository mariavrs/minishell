/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 03:31:33 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/13 01:53:44 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static int	run_redir_in(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->rdr->filename, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("minishell: ", 2), perror(cmd->rdr->filename),
			g_exit_status = 1);
	if (cmd->rdr->mode == '-')
		unlink(cmd->rdr->filename);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), perror("minishell: "), g_exit_status = 1);
	close(fd);
	return (0);
}

static int	run_redir_out(t_cmd *cmd)
{
	int	fd;

	if (cmd->rdr->mode == '>')
		fd = open(cmd->rdr->filename, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else
		fd = open(cmd->rdr->filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (fd < 0)
		return (ft_putstr_fd("minishell: ", 2), perror(cmd->rdr->filename),
			g_exit_status = 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), perror("minishell: "), g_exit_status = 1);
	close(fd);
	return (0);
}

int	run_redir(t_msh *msh, t_cmd *cmd)
{
	if (!cmd->rdr)
		return (0);
	if (cmd->rdr->mode == '<' || cmd->rdr->mode == '-')
	{
		if (run_redir_in(cmd))
			return (1);
	}
	else
	{
		if (run_redir_out(cmd))
			return (1);
	}
	ft_free_redir_elem(&cmd->rdr);
	return (run_redir(msh, cmd));
}
