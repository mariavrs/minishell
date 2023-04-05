/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:28:59 by mvorslov          #+#    #+#             */
/*   Updated: 2023/04/03 01:41:05 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

extern int	g_exit_status;

void	exec_pipeline(t_msh *msh)
{
	if (!msh->pipeline->next)
		run_cmd_exec(msh, msh->pipeline);
	else
		run_pipe(msh, msh->pipeline);
}

t_cmd	*parse_pipe(char *line, char *eline, t_msh *msh)
{
	t_cmd	*cmd;
	char	*del;
	int		quo_flag;

	trim_whitespaces(&line, &eline);
	del = eline - 1;
	quo_flag = 0;
	while (del >= line && (*del != '|' || quo_flag))
	{
		quo_flag = quo_check(*del, quo_flag);
		del--;
	}
	if (del >= line)
		cmd = parse_pipe(line, del, msh);
	cmd = parse_simple_cmd(del + 1, eline, msh);
	if (del >= eline)
		cmd->next = parse_pipe(del + 1, eline, msh);
	return (cmd);
}

static int	list_delim_locator(char *line, char *eline, char **del)
{
	int	block_check;
	int	quo_flag;

	block_check = 0;
	quo_flag = 0;
	*del = eline - 1;
	while (*del > line && !(!block_check && !quo_flag
			&& ((**del == '&' && *(*del - 1) == '&')
				|| (**del == '|' && *(*del - 1) == '|'))))
	{
		if (**del == ')' && !quo_flag)
			block_check++;
		else if (**del == '(' && !quo_flag)
			block_check--;
		else
			quo_flag = quo_check(**del, quo_flag);
		*del = *del - 1;
	}
	if (*del == line)
		return (0);
	*del = *del - 1;
	return (1);
}

void	parse_list(char *line, char *eline, t_msh *msh)
{
	char	*del;
//	int		stop_sig;

	trim_whitespaces(&line, &eline);
	trim_brackets(&line, &eline);
	if (!list_delim_locator(line, eline, &del))
	{
//		stop_sig;
		msh->pipeline = parse_pipe(line, eline, msh);
		exec_pipeline(msh);
		ft_free_pipeline(&msh->pipeline);
		return ;
	}
	parse_list(line, del, msh);
	if ((g_exit_status == 0 && *del == '&')
		|| (g_exit_status != 0 && *del == '|'))
		parse_list(del + 2, eline, msh);
}
