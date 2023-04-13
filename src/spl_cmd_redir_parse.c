/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 03:00:07 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/13 03:14:24 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static int	get_len_in_cmd(char *line)
{
	int	quo_flag;
	int	len;

	len = 0;
	quo_flag = quo_check(line[0], 0);
	while (line[len] && ((!is_in_str(line[len], STR_WHSPACE)
				&& !is_in_str(line[len], STR_REDIR)) || quo_flag))
		quo_flag = quo_check(line[++len], quo_flag);
	return (len);
}

static char	*get_filename_raw(t_msh *msh, t_cmd *cmd, int *i, int cursor)
{
	char	*filename_raw;
	char	tmp;

	tmp = cmd->spl_cmd[*i];
	cmd->spl_cmd[*i] = '\0';
	filename_raw = param_expansion(&cmd->spl_cmd[cursor], msh,
			quo_check(cmd->spl_cmd[cursor], 0), 0);
	cmd->spl_cmd[*i] = tmp;
	return (filename_raw);
}

static char	*get_redir_filename(t_msh *msh, t_cmd *cmd, int *i)
{
	char	*filename_raw;
	char	*filename;
	int		cursor;

	cursor = *i;
	*i += get_len_in_cmd(&cmd->spl_cmd[*i]);
	filename_raw = get_filename_raw(msh, cmd, i, cursor);
	if (!filename_raw)
		return (cmd->parse_status = 1, NULL);
	while (cursor < *i)
		cmd->spl_cmd[cursor++] = ' ';
	cursor = 0;
	filename = get_next_word(filename_raw, &cursor, 0,
			quo_check(*filename_raw, 0));
	if (!filename)
		return (cmd->parse_status = 1, NULL);
	if ((size_t)cursor < ft_strlen(filename_raw))
	{
		ft_mini_perror(filename_raw, NULL, "ambigous redirect", 1);
		ft_free_str(&filename);
		cmd->parse_status = 1;
	}
	ft_free_str(&filename_raw);
	return (filename);
}

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

t_redir	*parse_redir(t_msh *msh, t_cmd *cmd, int i, int quo_flag)
{
	t_redir	*rdr;

	while (cmd->spl_cmd[i] && ((cmd->spl_cmd[i] != '<'
				&& cmd->spl_cmd[i] != '>') || quo_flag))
		quo_flag = quo_check(cmd->spl_cmd[++i], quo_flag);
	if (!cmd->spl_cmd[i])
		return (NULL);
	rdr = NULL;
	rdr = malloc(sizeof(t_redir));
	if (!rdr)
		return (malloc_error(), cmd->parse_status = 1, NULL);
	rdr->mode = get_redir_mode(cmd, i);
	while (cmd->spl_cmd[i] == '<' || cmd->spl_cmd[i] == '>')
		cmd->spl_cmd[i++] = ' ';
	while (is_in_str(cmd->spl_cmd[i], STR_WHSPACE))
		i++;
	rdr->filename = get_redir_filename(msh, cmd, &i);
	if (cmd->parse_status)
		return (ft_free_redir(&rdr), NULL);
	if (rdr->mode == '-')
		cmd->parse_status = redir_heredoc(msh, rdr);
	if (cmd->parse_status)
		return (ft_free_redir(&rdr), NULL);
	return (rdr->next = parse_redir(msh, cmd, i, quo_flag), rdr);
}
