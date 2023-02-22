/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/22 14:38:21 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

char	**g_envp[2];

void	parse_exec_prep(char *sline, char **envp)
{
	char		*line;
	char		*eline;
	static int	exit_status;

	line = sline;
	eline = line + ft_strlen(line);
	if (trim_whitespaces(&line, &eline))
		return ;
	if (!is_in_str(*sline, STR_WHSPACE))
		add_history(sline);
	if (!syntax_check_prep(line, eline))
		ft_exec_tree(parse_list(line, eline), &exit_status, envp);
	else
		exit_status = 2;
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
	if (ft_malloc_envp(envp))
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
