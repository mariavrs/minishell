/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:26:27 by mvorslov          #+#    #+#             */
/*   Updated: 2023/03/31 00:15:30 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

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

int	redir_heredoc(char *delim, t_redir *rdr, t_msh *msh)
{
	t_heredoc	hd;

	fstat(STDIN_FILENO, &hd.statbuf);
	hd.hdoc_id = ft_itoa(hd.statbuf.st_atim.tv_sec);
	hd.hdoc = ft_strjoin("/tmp/minishell-", hd.hdoc_id);
	ft_free_str(&hd.hdoc_id);
	rdr->fd = open(hd.hdoc,
			O_CREAT | O_WRONLY | O_APPEND | O_TRUNC, 0444);
	if (rdr->fd < 0)
		return (perror("minishell: heredoc"), 1);
	hd.line_in = NULL;
	hd.line_in = readline("> ");
	while (hd.line_in && ft_strncmp(hd.line_in, delim,
			ft_strlen(delim) + 1))
	{
		write_to_heredoc(rdr, &hd, msh);
		hd.line_in = readline("> ");
	}
	close(rdr->fd);
	rdr->fd = open(hd.hdoc, O_RDONLY);
	if (rdr->fd < 0)
		return (ft_free_str(&hd.line_in), perror("minishell: heredoc"), 1);
	unlink(hd.hdoc);
	ft_free_str(&hd.hdoc);
	return (ft_free_str(&hd.line_in), 0);
}

int	redir_in(char *filename, t_redir *rdr, t_msh *msh)
{
	if (rdr->mode == '<')
	{
		rdr->fd = open(filename, O_RDONLY);
		if (rdr->fd < 0)
			return (ft_putstr_fd("minishell: ", 2), perror(filename), 1);
	}
	else if (rdr->mode == '-')
	{
		if (redir_heredoc(filename, rdr, msh))
			return (1);
	}
	if (!rdr->stdin_cpy)
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
		return (ft_putstr_fd("minishell: ", 2), perror(filename), 1);
	if (!rdr->stdout_cpy)
		rdr->stdout_cpy = dup(STDOUT_FILENO);
	dup2(rdr->fd, STDOUT_FILENO);
	return (0);
}

void	redir_clean(t_redir *rdr)
{
	if (rdr->stdin_cpy)
	{
		dup2(rdr->stdin_cpy, STDIN_FILENO);
		close(rdr->stdin_cpy);
	}
	if (rdr->stdout_cpy)
	{
		dup2(rdr->stdout_cpy, STDOUT_FILENO);
		close(rdr->stdout_cpy);
	}
}
