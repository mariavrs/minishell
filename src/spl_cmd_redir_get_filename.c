/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_redir_get_filename.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:18:52 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/18 16:23:34 by mvorslov         ###   ########.fr       */
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

char	*get_redir_filename(t_msh *msh, t_cmd *cmd, int *i)
{
	char	*filename_raw;
	char	*filename;
	int		cursor;

	cursor = *i;
	*i += get_len_in_cmd(&cmd->spl_cmd[*i]);
	filename_raw = get_filename_raw(msh, cmd, i, cursor);
	if (!filename_raw)
		return (cmd->parse_status = ERR_MALLOC, NULL);
	while (cursor < *i)
		cmd->spl_cmd[cursor++] = ' ';
	cursor = 0;
	filename = get_next_word(filename_raw, &cursor, 0,
			quo_check(*filename_raw, 0));
	if (!filename)
		return (cmd->parse_status = ERR_MALLOC,
			ft_free_str(&filename_raw), NULL);
	if ((size_t)cursor < ft_strlen(filename_raw))
	{
		ft_mini_perror(filename_raw, NULL, "ambigous redirect", 1);
		ft_free_str(&filename);
		cmd->parse_status = 1;
	}
	ft_free_str(&filename_raw);
	return (filename);
}
