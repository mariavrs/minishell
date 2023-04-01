/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_hdoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:04:40 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/01 01:53:51 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	write_to_heredoc(t_redir *rdr, t_heredoc *hd, t_msh *msh)
{
	hd->line_out = NULL;
	hd->line_out = param_expansion(hd->line_in, msh,
			quo_check(*hd->line_in, 0));
	ft_putstr_fd(hd->line_out, rdr->fd);
	write(rdr->fd, "\n", 1);
	ft_free_str(&hd->line_out);
	ft_free_str(&hd->line_in);
}

void	ctrl_c_heredoc_handler(int sig)
{
	ft_putchar_fd('\n', 1);
	rl_clear_history();
	exit (128 + sig);
}

int	heredoc_collect(char *delim, t_heredoc *hd, t_redir *rdr, t_msh *msh)
{
	signal(SIGINT, &ctrl_c_heredoc_handler);
	hd->line_in = NULL;
	hd->line_in = readline("> ");
	while (hd->line_in
		&& ft_strncmp(hd->line_in, delim, ft_strlen(delim) + 1))
	{
		write_to_heredoc(rdr, hd, msh);
		hd->line_in = readline("> ");
	}
	close(rdr->fd);
	return (0);
}

int	heredoc_collect_status(pid_t pid)
{
	int	stat;

	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return(128 + WTERMSIG(stat));
	return (0);
}

void	heredoc_clean(t_heredoc *hd)
{
	unlink(hd->hdoc);
	ft_free_str(&hd->hdoc);
	ft_free_str(&hd->line_in);
}

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
		return(heredoc_clean(&hd), 0);
	}
	return (heredoc_clean(&hd), hd.status);
}
