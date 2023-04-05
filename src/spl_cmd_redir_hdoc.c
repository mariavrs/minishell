/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_hdoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:04:40 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/03 15:27:58 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

int	heredoc_prep(t_heredoc *hd)
{
	hd->status = 0;
	if (fstat(STDIN_FILENO, &hd->statbuf) == -1)
		return (perror("minishell"), 1);
	hd->line_in = NULL;
	hd->hdoc_id = NULL;
	hd->hdoc_id = ft_itoa(hd->statbuf.st_atim.tv_sec);
	if (!hd->hdoc_id)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	hd->hdoc = ft_strjoin("/tmp/minishell-", hd->hdoc_id);
	ft_free_str(&hd->hdoc_id);
	if (!hd->hdoc)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	return (0);
}

static void	write_to_heredoc(t_msh *msh, t_cmd *cmd, t_heredoc *hd)
{
	hd->line_out = NULL;
	hd->line_out = param_expansion(hd->line_in, msh,
			quo_check(*hd->line_in, 0));
	ft_putstr_fd(hd->line_out, cmd->fd_in);
	write(cmd->fd_in, "\n", 1);
	ft_free_str(&hd->line_out);
	ft_free_str(&hd->line_in);
}

/* static void	fd_and_signals(t_msh *msh)
{
	int	in_tty;
	int	out_tty;

	in_tty = isatty(STDIN_FILENO);
	out_tty = isatty(STDOUT_FILENO);
	if (in_tty && out_tty)
		signal(SIGINT, &ctrl_c_heredoc_handler);
	if (!out_tty)
	{
		signal(SIGINT, &ctrl_c_heredoc_pipe_handler);
		close(STDOUT_FILENO);
		dup2(msh->stdout_default, STDOUT_FILENO);
	}
	if (!in_tty)
	{
		signal(SIGINT, &ctrl_c_heredoc_pipe_handler);
		close(STDIN_FILENO);
		dup2(msh->stdin_default, STDIN_FILENO);
	}
} */

int	heredoc_collect(t_msh *msh, t_cmd *cmd, t_heredoc *hd, char *eof)
{
	signal(SIGINT, &ctrl_c_heredoc_handler);
	hd->line_in = NULL;
	hd->line_in = readline("> ");
	while (hd->line_in
		&& ft_strncmp(hd->line_in, eof, ft_strlen(eof) + 1))
	{
		write_to_heredoc(msh, cmd, hd);
		hd->line_in = readline("> ");
	}
//	close(cmd->fd_in);
	return (rl_clear_history(), 0);
}

int	heredoc_collect_status(pid_t pid)
{
	int	stat;

	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (128 + WTERMSIG(stat));
	return (0);
}
