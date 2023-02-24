/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-smet <ede-smet@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/23 17:42:17 by ede-smet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

void	parse_exec_prep(t_msh *msh)
{
	char		*line;
	char		*eline;

	line = msh->sline;
	eline = line + ft_strlen(line);
	if (trim_whitespaces(&line, &eline))
		return ;
	if (!is_in_str(*msh->sline, STR_WHSPACE))
		add_history(msh->sline);
	if (!syntax_check_prep(line, eline))
		parse_list(line, eline, msh);
	else
		msh->exit_status = 2;
}

int	main(int argc, char **argv, char **envp)
{
	t_msh		msh;

	(void)argc;
	(void)argv;
	ft_parent_env_cpy(&(msh.envp), envp);
	msh.envp_lcl = NULL;
	msh.envp_lcl = malloc(sizeof(char *));
	if (!msh.envp_lcl)
		return (write(2, "malloc error\n", 13), 1);
	msh.envp_lcl[0] = NULL;
	msh.exit_status = 0;
	while (1)
	{
		msh.sline = NULL;
		msh.sline = readline("\033[1;36mminishell>>> \033[0m");
		if (msh.sline)
		{
			if (ft_strlen(msh.sline) != 0)
				parse_exec_prep(&msh);
			free(msh.sline);
		}
	}
	return (free_table(msh.envp), 0);
}
