/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/13 15:43:12 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

static int	get_next_arg(t_cmd *cmd, char *line, int argc)
{
	char	*arg;
	int		eword;

	eword = 0;
	arg = get_next_word(line, &eword, 0, quo_check(*line, 0));
	if (!arg)
	{
		while (cmd->argv[argc])
			ft_free_str(&cmd->argv[argc++]);
		return (ERR_MALLOC);
	}
	if (!ft_strlen(arg) && !is_in_str(*line, STR_QUOTE))
	{
		if (parse_cmd_argv(cmd, line + eword, argc))
			return (ERR_MALLOC);
	}
	else
	{
		if (parse_cmd_argv(cmd, line + eword, ++argc))
			return (ERR_MALLOC);
		cmd->argv[argc - 1] = arg;
	}
	return (0);
}

int	parse_cmd_argv(t_cmd *cmd, char *line, int argc)
{
	while (is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
	{
		if (!argc)
			return (0);
		cmd->argv = ft_malloc_dbl_str(argc + 1);
		if (!cmd->argv)
			return (ERR_MALLOC);
	}
	else
		return (get_next_arg(cmd, line, argc));
	return (0);
}

static t_cmd	*cmd_prep(char *line, char *eline)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (malloc_error(), NULL);
	cmd->stdin_backup = -1;
	cmd->stdout_backup = -1;
	cmd->rdr_in_flag = 0;
	cmd->rdr_out_flag = 0;
	cmd->next = NULL;
	cmd->rdr = NULL;
	cmd->argv = NULL;
	cmd->argv_line = NULL;
	cmd->error_msg = NULL;
	cmd->spl_cmd = ft_malloc_str(eline - line + 2);
	if (!cmd->spl_cmd)
		return (free(cmd), cmd = NULL);
	ft_strlcpy(cmd->spl_cmd, line, eline - line + 1);
	cmd->parse_status = 0;
	return (cmd);
}

t_cmd	*parse_simple_cmd(char *line, char *eline, t_msh *msh)
{
	t_cmd	*cmd;
	int		skip;

	skip = 0;
	trim_whitespaces(&line, &eline);
	cmd = cmd_prep(line, eline);
	if (!cmd)
		return (NULL);
	cmd->rdr = parse_redir(msh, cmd, skip, 0);
	while (is_in_str(cmd->spl_cmd[skip], STR_WHSPACE))
		skip++;
	if (!cmd->parse_status && cmd->spl_cmd[skip])
		skip += var_declar_fraction_ln(cmd->spl_cmd);
	if (!cmd->parse_status && !cmd->spl_cmd[skip])
		cmd->parse_status = lcl_var_declaration(msh, cmd->spl_cmd);
	else if (!cmd->parse_status)
		cmd->argv_line = param_expansion(&cmd->spl_cmd[skip], msh,
				quo_check(cmd->spl_cmd[skip], 0), 0);
	if (!cmd->parse_status && cmd->argv_line)
		cmd->parse_status = parse_cmd_argv(cmd, cmd->argv_line, 0);
	else if (!cmd->parse_status && !cmd->argv_line)
		cmd->parse_status = ERR_MALLOC;
	if (cmd->parse_status)
		return (g_exit_status = cmd->parse_status, ft_free_cmd(&cmd), NULL);
	return (ft_free_str(&cmd->spl_cmd), ft_free_str(&cmd->argv_line), cmd);
}
