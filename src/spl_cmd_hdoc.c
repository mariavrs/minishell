/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:04:40 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/13 15:56:08 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static void	hdoc_name_unlink(char **fname)
{
	unlink(*fname);
	ft_free_str(fname);
}

static int	heredoc_prep(t_heredoc *hd, t_redir *rdr)
{
	hd->status = 0;
	if (fstat(STDIN_FILENO, &hd->statbuf) == -1)
		return (perror("minishell"), 1);
	hd->line_in = NULL;
	hd->hdoc_id = NULL;
	hd->hdoc_id = ft_itoa(hd->statbuf.st_atim.tv_sec);
	if (!hd->hdoc_id)
		return (malloc_error(), hd->status = ERR_MALLOC, 1);
	hd->hdoc = ft_strjoin("/tmp/minishell-", hd->hdoc_id);
	ft_free_str(&hd->hdoc_id);
	if (!hd->hdoc)
		return (malloc_error(), hd->status = ERR_MALLOC, 1);
	hd->eof = rdr->filename;
	rdr->filename = hd->hdoc;
	return (0);
}

static void	write_to_heredoc(t_msh *msh, t_heredoc *hd)
{
	hd->line_out = NULL;
	hd->line_out = param_expansion(hd->line_in, msh,
			quo_check(*hd->line_in, 0), 1);
	if (!hd->line_out)
		return (hd->status = ERR_MALLOC, hdoc_name_unlink(&hd->hdoc),
			ft_free_str(&hd->line_in));
	ft_putstr_fd(hd->line_out, hd->fd);
	write(hd->fd, "\n", 1);
	ft_free_str(&hd->line_out);
	ft_free_str(&hd->line_in);
}

static int	heredoc_collect(t_msh *msh, t_heredoc *hd)
{
	hd->fd = open(hd->hdoc,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0444);
	if (hd->fd < 0)
		return (perror("minishell: heredoc"), ft_free_exit(msh),
			ft_free_str(&hd->eof), ft_free_str(&hd->hdoc),
			hdoc_name_unlink(&hd->hdoc), 1);
	signal(SIGINT, &ctrl_c_heredoc_handler);
	hd->line_in = NULL;
	hd->line_in = readline("> ");
	while (hd->line_in
		&& ft_strncmp(hd->line_in, hd->eof, ft_strlen(hd->eof) + 1))
	{
		write_to_heredoc(msh, hd);
		if (hd->status != ERR_MALLOC)
			hd->line_in = readline("> ");
	}
	close(hd->fd);
	ft_free_exit(msh);
	ft_free_str(&hd->eof);
	ft_free_str(&hd->hdoc);
	return (hd->status);
}

int	redir_heredoc(t_msh *msh, t_redir *rdr)
{
	t_heredoc	hd;
	pid_t		pid;

	if (heredoc_prep(&hd, rdr))
		return (hd.status);
	signal_manager(MODE_INTR_HDC);
	pid = fork();
	if (pid == 0)
		exit(heredoc_collect(msh, &hd));
	if (pid > 0)
		hd.status = waitpid_collect_status(pid);
	else if (pid == -1)
	{
		perror("minishell");
		hd.status = ERR_FORK;
	}
	signal_manager(MODE_NITR);
	ft_free_str(&hd.eof);
	ft_free_str(&hd.line_in);
	if (hd.status)
		hdoc_name_unlink(&hd.hdoc);
	return (hd.status);
}
