/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/01/27 16:10:34 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	ft_exec_tree(t_cmd *cmd, int *exit_status, char **envp)
{
	if (!cmd)
		return ;
	else if (cmd->type == EXEC_CMD)
		run_exec((t_exec *)cmd, exit_status, envp);
	else if (cmd->type == REDIR_CMD)
		run_redir((t_redir *)cmd, exit_status, envp);
	else if (cmd->type == PIPE_CMD)
		run_pipe((t_pipe *)cmd, exit_status, envp);
	else if (cmd->type == LIST_CMD)
		run_list((t_lol *)cmd, exit_status, envp);
}

void	exec_prep(char *sline, char **envp)
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
				ft_exec_tree(ret, &exit_status, envp);
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

int	main(int argc, char **argv, char **envp)
{
	char		*sline;

	(void)argc;
	(void)argv;
/* 	int i = -1;
	while(envp[++i])
		printf("%s\n", envp[i]); */
	while (1)
	{
		sline = NULL;
		sline = readline("\033[1;36mminishell>>> \033[0m");
		if (sline)
		{
			if (ft_strlen(sline) != 0)
				exec_prep(sline, envp);
			free(sline);
		}
	}
	return (0);
}
