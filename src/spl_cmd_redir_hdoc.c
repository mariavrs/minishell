/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_hdoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:04:40 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/02 21:00:26 by mvorslov         ###   ########.fr       */
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

static void	write_to_heredoc(t_redir *rdr, t_heredoc *hd, t_msh *msh)
{
	hd->line_out = NULL;
	hd->line_out = param_expansion(hd->line_in, msh,
			quo_check(*hd->line_in, 0));
	ft_putstr_fd(hd->line_out, rdr->fd);
	write(rdr->fd, "\n", 1);
	ft_free_str(&hd->line_out);
	ft_free_str(&hd->line_in);
}

static void	fd_and_signals(t_msh *msh)
{
	if (msh->in_pipe_flag || msh->out_pipe_flag)
		signal(SIGINT, &ctrl_c_heredoc_pipe_handler);
	else
		signal(SIGINT, &ctrl_c_heredoc_handler);
	if (msh->in_pipe_flag)
	{
		close(STDIN_FILENO);
		dup2(msh->stdin_default, STDIN_FILENO);
	}
	if (msh->out_pipe_flag)
	{
		close(STDOUT_FILENO);
		dup2(msh->stdout_default, STDOUT_FILENO);
	}
}

int	heredoc_collect(char *delim, t_heredoc *hd, t_redir *rdr, t_msh *msh)
{
	fd_and_signals(msh);
	hd->line_in = NULL;
	hd->line_in = readline("> ");
	while (hd->line_in
		&& ft_strncmp(hd->line_in, delim, ft_strlen(delim) + 1))
	{
		write_to_heredoc(rdr, hd, msh);
		hd->line_in = readline("> ");
	}
	close(rdr->fd);
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
