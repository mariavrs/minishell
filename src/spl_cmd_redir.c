/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:26:27 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/02 23:49:04 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static void	heredoc_clean(t_heredoc *hd)
{
	unlink(hd->hdoc);
	ft_free_str(&hd->hdoc);
	ft_free_str(&hd->line_in);
}

int	redir_heredoc(t_msh *msh, t_cmd *cmd, char *eof)
{
	t_heredoc	hd;
	pid_t		pid;

	heredoc_prep(msh, &hd);
	cmd->fd_in = open(hd.hdoc,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0444);
	if (cmd->fd_in < 0)
		return (perror("minishell: heredoc"), 1);
	signal_manager(MODE_INTR_HDC);
	pid = fork();
	if (pid == 0)
		exit(heredoc_collect(msh, cmd, &hd, eof));
	hd.status = heredoc_collect_status(pid);
	close(cmd->fd_in);
	signal_manager(MODE_NITR);
	if (!hd.status)
	{
		cmd->fd_in = open(hd.hdoc, O_RDONLY);
		if (cmd->fd_in < 0)
			return (heredoc_clean(&hd), perror("minishell: heredoc"), 1);
		return (heredoc_clean(&hd), 0);
	}
	return (heredoc_clean(&hd), hd.status);
}

int	redir_in(t_msh *msh, t_cmd *cmd, char *filename)
{
	int	hdc_stat;

	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->rdr_mode == '<')
	{
		cmd->fd_in = open(filename, O_RDONLY);
		if (cmd->fd_in < 0)
			return (ft_putstr_fd("minishell: ", 2), perror(filename), 1);
	}
	else if (cmd->rdr_mode == '-')
	{
		hdc_stat = redir_heredoc(msh, cmd, filename);
		if (hdc_stat)
			return (hdc_stat);
	}
	return (0);
}

int	redir_out(t_cmd *cmd, char *filename)
{
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
	if (cmd->rdr_mode == '>')
		cmd->fd_out = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else if (cmd->rdr_mode == '+')
		cmd->fd_out = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (cmd->fd_out < 0)
		return (ft_putstr_fd("minishell: ", 2), perror(filename), 1);
	return (0);
}

void	redir_clean(t_msh *msh, t_cmd *cmd)
{
	if (cmd->fd_in >= 0)
	{
		dup2(msh->stdin_default, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out >= 0)
	{
		dup2(msh->stdout_default, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}
