/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 03:00:07 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/10 00:22:38 by mvorslov         ###   ########.fr       */
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

static char	*get_next_word_fn(char *src, int *src_i, int dest_i, int quo_flag)
{
	char	*dest;
	char	c;

	while (src[*src_i] && ((is_in_str(src[*src_i], STR_WHSPACE) && !quo_flag)
			|| (src[*src_i] == '\"' && quo_flag != 1)
			|| (src[*src_i] == '\'' && quo_flag != 2)))
		quo_flag = quo_check(src[++(*src_i)], quo_flag);
	if (src[*src_i] && !is_in_str(src[*src_i], STR_WHSPACE))
	{
		c = src[(*src_i)++];
		dest = get_next_word_fn(src, src_i, dest_i + 1, quo_flag);
		if (!dest)
			return (NULL);
		dest[dest_i] = c;
	}
	else
	{
		dest = NULL;
		dest = malloc(sizeof(char) * (dest_i + 1));
		if (!dest)
			return (malloc_error(), NULL);
		dest[dest_i] = '\0';
	}
	return (dest);
}


//static char	*get_redir_filename(t_msh *msh, t_cmd *cmd, int *i)
static char	*get_redir_filename(t_msh *msh, t_cmd *cmd, int *i)
{
	char	*filename_raw;
	char	*filename;
	char	tmp;
	int		cursor;

	cursor = *i;
	*i += get_len_in_cmd(&cmd->spl_cmd[*i]);
	tmp = cmd->spl_cmd[*i];
	cmd->spl_cmd[*i] = '\0';
	filename_raw = NULL;
	filename_raw = param_expansion(&cmd->spl_cmd[cursor], msh,
				quo_check(cmd->spl_cmd[cursor], 0));
	cmd->spl_cmd[*i] = tmp;
	if (!filename_raw)
		return (cmd->parse_status = 1, NULL);
	while (cursor < *i)
		cmd->spl_cmd[cursor++] = ' ';
	cursor = 0;
	filename = get_next_word_fn(filename_raw, &cursor, 0, quo_check(*filename_raw, 0));
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

static char	get_redir_mode(char *spl_cmd, int i)
{
	if (spl_cmd[i] == '>' && spl_cmd[i + 1] == '>')
		return ('+');
	else if (spl_cmd[i] == '<' && spl_cmd[i + 1] == '<')
		return ('-');
	else
		return (spl_cmd[i]);
}

static void	set_mode_flag(t_cmd *cmd, char mode)
{
	if (mode == '-' || mode == '<')
		cmd->rdr_in_flag = 1;
	if (mode == '+' || mode == '>')
		cmd->rdr_out_flag = 1;
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
		return (msh->malloc_err_parse = 1, cmd->parse_status = 1, NULL);
	rdr->mode = get_redir_mode(cmd->spl_cmd, i);
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
	set_mode_flag(cmd, rdr->mode);
	return (rdr->next = parse_redir(msh, cmd, i, quo_flag), rdr);
}
