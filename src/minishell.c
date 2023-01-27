/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/27 12:47:33 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	ft_exec_tree(t_cmd *cmd, int *exit_status)
{
	if (!cmd)
		return ;
	else if (cmd->type == EXEC_CMD)
		run_exec((t_exec *)cmd, exit_status);
	else if (cmd->type == REDIR_CMD)
		run_redir((t_redir *)cmd, exit_status);
	else if (cmd->type == PIPE_CMD)
		run_pipe((t_pipe *)cmd, exit_status);
	else if (cmd->type == LIST_CMD)
		run_list((t_lol *)cmd, exit_status);
}

void	exec_prep(char *sline)
{
	t_cmd		*ret;
	char		*line;
	char		*eline;
	static int	exit_status;

	line = sline;
	eline = line + ft_strlen(line);
	if (!trim_whitespaces(&line, &eline))
	{
		if (!check_whitespace(*sline))
			add_history(sline);
		if (!brackets_check(line, eline))
		{
			ret = parse_list(line, eline);
			if (ret)
				ft_exec_tree(ret, &exit_status);
			else
				exit_status = 2;//syntax error
		}
 		else
		{
			printf("minishell: syntax error: incorrect usage of parentheses\n");
			exit_status = 2;
		}
	}
}

int	main(void)
{
	char		*sline;

	while (1)
	{
		sline = NULL;
		sline = readline("\033[1;36mminishell>>> \033[0m");
		if (sline)
		{
			if (ft_strlen(sline) != 0)
				exec_prep(sline);
			free(sline);
		}
	}
	return (0);
}
