/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/03 00:57:16 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static int	get_next_arg(t_msh *msh, t_cmd *cmd, char *line, int argc)
{
	char	*arg;
	int		eword;

	eword = 0;
	arg = get_next_word(line, msh, &eword);
	if (!arg)
		return (1);
	if (!ft_strlen(arg) && !is_in_str(*line, STR_QUOTE))
	{
		if (parse_cmd_argv(msh, cmd, line + eword, argc))
			return (1);
	}
	else
	{
		if (parse_cmd_argv(msh, cmd, line + eword, ++argc))
			return (1);
		cmd->argv[argc - 1] = arg;
	}
	return (0);
}

int	parse_cmd_argv(t_msh *msh, t_cmd *cmd, char *line, int argc)
{
	while (is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
	{
		if (!argc)
			return (0);
		cmd->argv = malloc(sizeof(char *) * (argc + 1));
		if (!cmd->argv)
			return (malloc_error(msh), 1);
		cmd->argv[argc] = NULL;
	}
	else
		return (get_next_arg(msh, cmd, line, argc));
	return (0);
}

int	run_redir(t_cmd *cmd, char *line, int *i, t_msh *msh)
{
	char	*filename;
	int		l_start;
	int		status_lcl;

	l_start = *i;
	filename = NULL;
	filename = get_next_word(line, msh, i);
	if (!filename)
		return (malloc_error(msh), 1);
	if (cmd->rdr_mode == '>' || cmd->rdr_mode == '+')
		status_lcl = redir_out(cmd, filename);
	else
		status_lcl = redir_in(msh, cmd, filename);
	while (l_start < *i)
		line[l_start++] = ' ';
	return (ft_free_str(&filename), status_lcl);
}

int	parse_redir(t_msh *msh, t_cmd *cmd, char *line, int i)
{
	int	status_lcl;
	int	quo_flag;

	quo_flag = quo_check(*line, 0);
	while (line[i])
	{
		while (line[i] && ((line[i] != '<' && line[i] != '>') || quo_flag))
			quo_flag = quo_check(line[++i], quo_flag);
		if (!line[i])
			return (0);
		if (line[i] && line[i] != line[i + 1])
			cmd->rdr_mode = line[i];
		else if (line[i] == '>' && line[i + 1] == '>')
			cmd->rdr_mode = '+';
		else if (line[i] == '<' && line[i + 1] == '<')
			cmd->rdr_mode = '-';
		while (line[i] == '<' || line[i] == '>')
			line[i++] = ' ';
		while (is_in_str(line[i], STR_WHSPACE))
			i++;
		status_lcl = run_redir(cmd, line, &i, msh);
		if (status_lcl)
			return (status_lcl);
	}
	return (0);
}

t_cmd	*parse_simple_cmd(char *line, char *eline, t_msh *msh)
{
	t_cmd	*cmd;
	int		status_lcl;
	int		skip;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (malloc_error(msh), NULL);
	cmd->next = NULL;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	skip = 0;
	status_lcl = 0;
	trim_whitespaces(&line, &eline);
	cmd->argv = NULL;
	cmd->spl_cmd = ft_malloc_str(msh, eline - line + 2);
	if (!cmd->spl_cmd)
		return (free(cmd), cmd = NULL);
	ft_strlcpy(cmd->spl_cmd, line, eline - line + 1);
	if (!(*cmd->spl_cmd >= '0' && *cmd->spl_cmd <= '9'))
		status_lcl = first_wrd_check(&skip, cmd->spl_cmd, msh);
	if (!status_lcl && cmd->spl_cmd[skip])
		status_lcl = parse_redir(msh, cmd, cmd->spl_cmd, skip);
	if (!status_lcl && cmd->spl_cmd[skip])
		status_lcl = parse_cmd_argv(msh, cmd, &cmd->spl_cmd[skip], 0);
	if (status_lcl)
		g_exit_status = status_lcl;
	if (status_lcl >= 128 || msh->malloc_err == 1)
		return (ft_free_cmd(&cmd), NULL);
	return (ft_free_str(&cmd->spl_cmd), cmd);
}

