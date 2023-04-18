/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 03:00:07 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/18 16:19:17 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static char	get_redir_mode(t_cmd *cmd, int i)
{
	if (cmd->spl_cmd[i] == '>')
	{
		cmd->rdr_out_flag = 1;
		if (cmd->spl_cmd[i + 1] == '>')
			return ('+');
	}
	else if (cmd->spl_cmd[i] == '<')
	{
		cmd->rdr_in_flag = 1;
		if (cmd->spl_cmd[i + 1] == '<')
			return ('-');
	}
	return (cmd->spl_cmd[i]);
}

static t_redir	*redir_prep(t_cmd *cmd, int i)
{
	t_redir	*rdr;

	rdr = NULL;
	rdr = malloc(sizeof(t_redir));
	if (!rdr)
		return (malloc_error(), NULL);
	rdr->next = NULL;
	rdr->mode = get_redir_mode(cmd, i);
	rdr->filename = NULL;
	return (rdr);
}

t_redir	*parse_redir(t_msh *msh, t_cmd *cmd, int i, int quo_flag)
{
	t_redir	*rdr;

	while (cmd->spl_cmd[i] && ((cmd->spl_cmd[i] != '<'
				&& cmd->spl_cmd[i] != '>') || quo_flag))
		quo_flag = quo_check(cmd->spl_cmd[++i], quo_flag);
	if (!cmd->spl_cmd[i])
		return (NULL);
	rdr = redir_prep(cmd, i);
	if (!rdr)
		return (cmd->parse_status = ERR_MALLOC, NULL);
	while (cmd->spl_cmd[i] == '<' || cmd->spl_cmd[i] == '>')
		cmd->spl_cmd[i++] = ' ';
	while (is_in_str(cmd->spl_cmd[i], STR_WHSPACE))
		i++;
	if (rdr->mode == '-')
		cmd->parse_status = redir_heredoc(msh, cmd, &i, rdr);
	else
		rdr->filename = get_redir_filename(msh, cmd, &i);
	if (cmd->parse_status)
		return (ft_free_redir(&rdr), NULL);
	rdr->next = parse_redir(msh, cmd, i, quo_flag);
	if (cmd->parse_status)
		return (ft_free_redir(&rdr), NULL);
	return (rdr);
}
