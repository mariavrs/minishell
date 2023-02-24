/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/02/24 19:56:14 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	sline_cmp_len(t_msh *msh)
{
	int	s_len;
	int	ex_s_len;

	s_len = ft_strlen(msh->sline);
	ex_s_len = ft_strlen(msh->ex_sline);
	if (s_len > ex_s_len)
		return (s_len + 1);
	else
		return (ex_s_len + 1);
}

void	parse_exec_prep(t_msh *msh)
{
	char	*line;
	char	*eline;

	line = msh->sline;
	eline = line + ft_strlen(line);
	if (trim_whitespaces(&line, &eline))
		return ;
	if (!is_in_str(*msh->sline, STR_WHSPACE)
		&& ft_strncmp(msh->sline, msh->ex_sline, sline_cmp_len(msh)))
	{
		add_history(msh->sline);
		if (msh->ex_sline)
			free(msh->ex_sline);
		msh->ex_sline = ft_strdup(msh->sline);
	}
	if (!syntax_check_prep(line, eline))
		parse_list(line, eline, msh);
	else
		msh->exit_status = 2;
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	ft_parent_env_cpy(&(msh.envp), envp);
	msh.envp_lcl = NULL;
	msh.envp_lcl = malloc(sizeof(char *));
	if (!msh.envp_lcl)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	msh.envp_lcl[0] = NULL;
	msh.exit_status = 0;
	msh.ex_sline = NULL;
	while (1)
	{
		msh.sline = NULL;
		msh.sline = readline("\033[1;36mminishell>> \033[0m");
		if (msh.sline)
		{
			if (ft_strlen(msh.sline) != 0)
				parse_exec_prep(&msh);
			free(msh.sline);
		}
	}
}
