/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:04:40 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/09 03:25:05 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static int	heredoc_prep(t_msh *msh, t_heredoc *hd, t_redir *rdr)
{
	hd->status = 0;
	if (fstat(STDIN_FILENO, &hd->statbuf) == -1)
		return (perror("minishell"), 1);
	hd->line_in = NULL;
	hd->hdoc_id = NULL;
	hd->hdoc_id = ft_itoa(hd->statbuf.st_atim.tv_sec);
	if (!hd->hdoc_id)
		return (malloc_error(), msh->malloc_err_parse = 1);
	hd->hdoc = ft_strjoin("/tmp/minishell-", hd->hdoc_id);
	ft_free_str(&hd->hdoc_id);
	if (!hd->hdoc)
		return (malloc_error(), msh->malloc_err_parse = 1);
	hd->eof = rdr->filename;
	rdr->filename = hd->hdoc;
	return (0);
}

static void	write_to_heredoc(t_msh *msh, t_heredoc *hd)
{
	hd->line_out = NULL;
	hd->line_out = param_expansion(hd->line_in, msh,
			quo_check(*hd->line_in, 0));
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
			ft_free_str(&hd->eof), ft_free_str(&hd->hdoc), 1);
	signal(SIGINT, &ctrl_c_heredoc_handler);
	hd->line_in = NULL;
	hd->line_in = readline("> ");
	while (hd->line_in
		&& ft_strncmp(hd->line_in, hd->eof, ft_strlen(hd->eof) + 1))
	{
		write_to_heredoc(msh, hd);
		hd->line_in = readline("> ");
	}
	close(hd->fd);
	ft_free_exit(msh);
	ft_free_str(&hd->eof);
	ft_free_str(&hd->hdoc);
	return (0);
}

static int	heredoc_collect_status(pid_t pid)
{
	int	stat;

	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (128 + WTERMSIG(stat));
	return (0);
}

int	redir_heredoc(t_msh *msh, t_redir *rdr)
{
	t_heredoc	hd;
	pid_t		pid;

	if (heredoc_prep(msh, &hd, rdr))
		return (1);
	signal_manager(MODE_INTR_HDC);
	pid = fork();
	if (pid == 0)
		exit(heredoc_collect(msh, &hd));
	hd.status = heredoc_collect_status(pid);
	signal_manager(MODE_NITR);
	ft_free_str(&hd.eof);
	ft_free_str(&hd.line_in);
	return (hd.status);
}

/* void	redir_clean(t_msh *msh, t_cmd *cmd)
{
	(void)msh;
	if (!isatty(STDIN_FILENO))
		dup2(msh->stdin_default, STDIN_FILENO);
	if (!isatty(STDOUT_FILENO))
		dup2(msh->stdout_default, STDOUT_FILENO);
	if (cmd->fd_in >= 0)
		close(cmd->fd_in);
	if (cmd->fd_out >= 0)
		close(cmd->fd_out);
} */