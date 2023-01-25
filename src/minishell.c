/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/25 14:47:28 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	ft_exec_tree(t_cmd *cmd, int exit_status)
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

int	main(void)
{
	char		*line;
	char		*sline;
	char		*eline;
	static int	exit_status;

	while (1)
	{
		sline = NULL;
		sline = readline("\033[1;36mminishell>>> \033[0m");
		if (sline)
		{
			if (ft_strlen(sline) != 0)
			{
				line = sline;
				eline = line + ft_strlen(line) - 1;
				if (!trim_whitespaces(&line, &eline))
				{
					if (sline == line)
						add_history(sline);
					if (!brackets_check(line, eline))
						ft_exec_tree(parse_list(line, eline), exit_status);
	/* 				else
						panic_runaway(); */
				}
			}
			free(sline);
		}
	}
	return (0);
}
