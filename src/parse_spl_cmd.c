/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spl_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:49:24 by mvorslov          #+#    #+#             */
/*   Updated: 2023/02/23 15:37:13 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	redir_info(char *line, char *mode)
{
	int		count;

	count = 1;
	if (*line != *(line + 1))
		*mode = *line;
	else if (*line == '<')
		*mode = '-';
	else
		*mode = '+';
	if (*line == *(line + 1))
		count++;
	while (*(line + count) && is_in_str(*(line + count), STR_WHSPACE))
		count++;
	return (count);
}

int	wrd_collect(char *line, t_cmd_bld *bld)
{
	int	count;
	int	quo_flag;

	count = 0;
	quo_flag = quo_check(*line, 0);
	if (quo_flag)
	{
		line++;
		bld->quote = 1;
		quo_flag = quo_check(*(line + count), quo_flag);
		while (*(line + count) && quo_flag)
		{
			count++;
			quo_flag = quo_check(*(line + count), quo_flag);
		}
	}
	else
	{
		while (*(line + count) && !is_in_str(*(line + count), STR_WHSPACE)
			&& !is_in_str(*(line + count), STR_QUOTE)
			&& !is_in_str(*(line + count), STR_REDIR))
			count++;
	}
	return (count);
}

int	fill_the_struct(t_spl_cmd *cmd, int argc, int redirc, t_cmd_bld	bld)
{
	char	*str;

	str = NULL;
	str = malloc(sizeof(char) * (bld.symb_count + 1));
	if (!str)
		return (ft_putstr_fd("minishell: malloc error\n", 2), 1);
	str[bld.symb_count] = '\0';
	while (--bld.symb_count >= 0)
		str[bld.symb_count] = *(bld.line + bld.symb_count);
	if (bld.mode)
	{
		cmd->redir[redirc - 1].file = str;
		cmd->redir[redirc - 1].mode = bld.mode;
	}
	else
		cmd->argv[argc - 1] = str;
	return (0);
}

int	build_the_struct(t_spl_cmd *cmd, char *line, int argc, int redirc)
{
	t_cmd_bld	bld;

	bld.symb_count = 0;
	bld.mode = '\0';
	bld.quote = 0;
	while (line && is_in_str(*line, STR_WHSPACE))
		line++;
	if (!(*line))
		return (ft_malloc_spl_cmd(cmd, argc, redirc));
	if (is_in_str(*line, STR_REDIR))
	{
		line += redir_info(line, &bld.mode);
		redirc++;
	}
	else
		argc++;
	bld.symb_count = wrd_collect(line, &bld);
	line += bld.quote;
	if (build_the_struct(cmd, line + bld.symb_count + bld.quote, argc, redirc))
		return (1);
	bld.line = line;
	return (fill_the_struct(cmd, argc, redirc, bld));
}

void	parse_simple_cmd(char *line, char *eline, t_msh *msh)
{
	t_spl_cmd	cmd;

	trim_whitespaces(&line, &eline);
	*eline = '\0';
//	line = first_wrd_check(line, msh);
	line = param_expansion(line, msh);
	if (build_the_struct(&cmd, line, 0, 0))
		return (free(line), ft_free_redir_info(&cmd), ft_free_argv(&cmd));
	free(line);
	cmd.stdin_cpy = 0;
	cmd.stdout_cpy = 0;
	run_spl_cmd(&cmd, msh);
}
