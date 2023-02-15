/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/14 13:24:17 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	parse_exec_prep(char *sline, char **envp)
{
	t_cmd		*cmd;
	char		*line;
	char		*eline;
	static int	exit_status;

	line = sline;
	eline = line + ft_strlen(line);
	cmd = NULL;
	if (trim_whitespaces(&line, &eline))
		return ;
	if (!check_if_in_str(*sline, STR_WHSPACE))
		add_history(sline);
	if (quo_stx_check(line, eline))
		write(2, "minishell: syntax error: unclosed quotes\n", 41);
	else if (brackets_check(line, eline))
		write(2, "minishell: syntax error: unclosed parentheses\n", 46);
 	else
		cmd = parse_list(line, eline);
	if (cmd)
		ft_exec_tree(cmd, &exit_status, envp);
	else
		exit_status = 2;//syntax error
}

int	ft_malloc_envp(char **envp)
{
	g_envp[0] = envp;
	g_envp[1] = NULL;
	g_envp[1] = malloc(sizeof(char *));
	if (!g_envp[1])
		return (1);
	g_envp[1][0] = NULL;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*sline;

	(void)argc;
	(void)argv;
	if (ft_malloc_envp)
		return (write(2, "malloc error\n", 13), 1);
	while (1)
	{
		sline = NULL;
		sline = readline("\033[1;36mminishell>>> \033[0m");
		if (sline)
		{
			if (ft_strlen(sline) != 0)
				parse_exec_prep(sline, envp);
			free(sline);
		}
	}
	return (0);
}
