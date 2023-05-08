/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:04:40 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/22 02:37:40 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

typedef struct s_heredoc
{
	int			fd;
	int			expand_flag;
	char		*eof;
	char		*line_in;
	char		*line_out;
	char		*hdoc_id;
	int			status;
	struct stat	statbuf;
}	t_heredoc;

static void	write_to_heredoc(t_msh *msh, t_heredoc *hd, char *filename)
{
	if (!hd->expand_flag)
		return (ft_putendl_fd(hd->line_in, hd->fd), ft_free_str(&hd->line_in));
	hd->line_out = NULL;
	hd->line_out = param_expansion(hd->line_in, msh, -1, 0);
	if (!hd->line_out)
		return (hd->status = ERR_MALLOC, unlink(filename),
			ft_free_str(&hd->line_in));
	ft_putendl_fd(hd->line_out, hd->fd);
	ft_free_str(&hd->line_out);
	ft_free_str(&hd->line_in);
}

static int	heredoc_collect(t_msh *msh, t_heredoc *hd, char *filename)
{
	hd->fd = open(filename,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0444);
	if (hd->fd < 0)
		return (perror("minishell: heredoc"), unlink(filename),
			ft_free_exit(msh), ft_free_str(&hd->eof), 1);
	signal(SIGINT, &ctrl_c_heredoc_handler);
	hd->line_in = NULL;
	hd->line_in = readline("> ");
	while (hd->line_in
		&& ft_strncmp(hd->line_in, hd->eof, ft_strlen(hd->eof) + 1))
	{
		write_to_heredoc(msh, hd, filename);
		if (!hd->status)
			hd->line_in = readline("> ");
	}
	close(hd->fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (hd->status);
}

static int	check_if_expand_and_clean(char *spl_cmd, int start, int end)
{
	int	expand_flag;

	expand_flag = 1;
	while (start < end)
	{
		if (is_in_str(spl_cmd[start], STR_QUOTE))
			expand_flag = 0;
		spl_cmd[start++] = ' ';
	}
	return (expand_flag);
}

static int	heredoc_prep(t_heredoc *hd, t_cmd *cmd, int *i, t_redir *rdr)
{
	int	start;

	start = *i;
	hd->status = 0;
	hd->line_in = NULL;
	hd->hdoc_id = NULL;
	if (fstat(STDIN_FILENO, &hd->statbuf) == -1)
		return (perror("minishell"), hd->status = 1);
	hd->eof = get_next_word(cmd->spl_cmd, i, 0, quo_check(cmd->spl_cmd[*i], 0));
	if (!hd->eof)
		return (hd->status = ERR_MALLOC);
	hd->expand_flag = check_if_expand_and_clean(cmd->spl_cmd, start, *i);
	hd->hdoc_id = ft_itoa(hd->statbuf.st_atim.tv_sec);
	if (!hd->hdoc_id)
		return (malloc_error(), ft_free_str(&hd->eof), hd->status = ERR_MALLOC);
	rdr->filename = ft_strjoin("/tmp/minishell-", hd->hdoc_id);
	ft_free_str(&hd->hdoc_id);
	if (!rdr->filename)
		return (malloc_error(), ft_free_str(&hd->eof), hd->status = ERR_MALLOC);
	return (0);
}

int	redir_heredoc(t_msh *msh, t_cmd *cmd, int *i, t_redir *rdr)
{
	t_heredoc	hd;
	pid_t		pid;

	if (heredoc_prep(&hd, cmd, i, rdr))
		return (hd.status);
	signal_manager(MODE_INTR_HDC);
	pid = fork();
	if (pid == 0)
		exit(heredoc_collect(msh, &hd, rdr->filename));
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
		unlink(rdr->filename);
	return (hd.status);
}
