/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/24 21:26:17 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	ft_exec_tree(t_cmd *cmd, int exit_status)
{
	if (!cmd)
		return (0);
	else if (cmd->type == EXEC_CMD)
		run_exec((t_exec *)cmd, exit_status);
	else if (cmd->type == REDIR_CMD)
		run_redir((t_redir *)cmd, exit_status);
	else if (cmd->type == PIPE_CMD)
		run_pipe((t_pipe *)cmd, exit_status);
	else if (cmd->type == LIST_CMD)
		run_list((t_list *)cmd, exit_status);
	return (0);
}

t_cmd	*ft_parse(char *line)
{
	t_cmd	*ret;
	char	*eline;

	eline = line + ft_strlen(line);
	ret = parse_list(line, eline);
	return (ret);
}

int	main(void)
{
	char	*line;
	static int	exit_status;

	while (1)
	{
		line = readline("\033[1;36mminishell>>> \033[0m");
		if (ft_strlen(line) != 0)
		{
			add_history(line);
			ft_exec_tree(ft_parse(line), exit_status);
		}
		free(line);
	}
	return (0);
}
