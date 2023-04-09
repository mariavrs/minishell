/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_cmd_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/09 03:14:15 by mvorslov         ###   ########.fr       */
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
			return (malloc_error(), msh->malloc_err_parse = 1);
		cmd->argv[argc] = NULL;
	}
	else
		return (get_next_arg(msh, cmd, line, argc));
	return (0);
}

static t_cmd	*cmd_prep(t_msh *msh, char *line, char *eline)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (msh->malloc_err_parse = 1, malloc_error(), NULL);
	cmd->stdin_backup = -1;
	cmd->stdout_backup = -1;
	cmd->rdr_in_flag = 0;
	cmd->rdr_out_flag = 0;
	cmd->next = NULL;
	cmd->rdr = NULL;
	cmd->argv = NULL;
	cmd->spl_cmd = ft_malloc_str(eline - line + 2);
	if (!cmd->spl_cmd)
		return (msh->malloc_err_parse = 1, free(cmd), cmd = NULL);
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
	cmd = cmd_prep(msh, line, eline);
	if (!cmd)
		return (NULL);
	if (!(*cmd->spl_cmd >= '0' && *cmd->spl_cmd <= '9'))
		cmd->parse_status = first_wrd_check(&skip, cmd->spl_cmd, msh);
	if (!cmd->parse_status && cmd->spl_cmd[skip])
		cmd->rdr = parse_redir(msh, cmd, skip, 0);
	if (!cmd->parse_status && cmd->spl_cmd[skip])
		cmd->parse_status = parse_cmd_argv(msh, cmd, &cmd->spl_cmd[skip], 0);
	if (cmd->parse_status)
		g_exit_status = cmd->parse_status;
	if (cmd->parse_status > 128 || msh->malloc_err_parse == 1)
		return (ft_free_cmd(&cmd), NULL);
	return (ft_free_str(&cmd->spl_cmd), cmd);
}
