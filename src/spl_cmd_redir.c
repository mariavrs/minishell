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

int	redir_heredoc(char *delim, t_redir *rdr, t_msh *msh)
{
	t_heredoc	hd;
	pid_t		pid;

	heredoc_prep(&hd);
	rdr->fd = open(hd.hdoc,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0444);
	if (rdr->fd < 0)
		return (perror("minishell: heredoc"), 1);
	signal_manager(MODE_INTR_HDC);
	pid = fork();
	if (pid == 0)
		exit(heredoc_collect(delim, &hd, rdr, msh));
	hd.status = heredoc_collect_status(pid);
	signal_manager(MODE_NITR);
	if (!hd.status)
	{
		rdr->fd = open(hd.hdoc, O_RDONLY);
		if (rdr->fd < 0)
			return (heredoc_clean(&hd), perror("minishell: heredoc"), 1);
		return (heredoc_clean(&hd), 0);
	}
	return (heredoc_clean(&hd), hd.status);
}

int	redir_in(char *filename, t_redir *rdr, t_msh *msh)
{
	int	hdc_stat;

	if (rdr->mode == '<')
	{
		rdr->fd = open(filename, O_RDONLY);
		if (rdr->fd < 0)
			return (error_custom_arg(filename, ": "), perror(""), 1);
	}
	else if (rdr->mode == '-')
	{
		hdc_stat = redir_heredoc(filename, rdr, msh);
		if (hdc_stat)
			return (hdc_stat);
	}
	if (rdr->stdin_cpy == -1)
		rdr->stdin_cpy = dup(STDIN_FILENO);
	dup2(rdr->fd, STDIN_FILENO);
	return (0);
}

int	redir_out(char *filename, t_redir *rdr)
{
	if (rdr->mode == '>')
		rdr->fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else if (rdr->mode == '+')
		rdr->fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (rdr->fd < 0)
		return (error_custom_arg(filename, ": "), perror(""), 1);
	if (rdr->stdout_cpy == -1)
		rdr->stdout_cpy = dup(STDOUT_FILENO);
	dup2(rdr->fd, STDOUT_FILENO);
	return (0);
}

void	redir_clean(t_redir *rdr)
{
	if (rdr->stdin_cpy >= 0)
	{
		dup2(rdr->stdin_cpy, STDIN_FILENO);
		close(rdr->stdin_cpy);
	}
	if (rdr->stdout_cpy >= 0)
	{
		dup2(rdr->stdout_cpy, STDOUT_FILENO);
		close(rdr->stdout_cpy);
	}
}
