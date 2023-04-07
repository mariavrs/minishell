/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvorslov <mvorslov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 22:28:07 by ede-smet          #+#    #+#             */
/*   Updated: 2023/04/03 02:08:51 by mvorslov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mini_fun.h"

int	g_exit_status;

static void	exec_pipeline(t_msh *msh)
{
	if (!msh->cmd_list->pipeline->next)
		run_cmd_exec(msh, msh->cmd_list->pipeline);
	else
		run_pipe(msh, msh->cmd_list->pipeline);
}

static void	exec_cmd_list(t_msh *msh)
{
	t_block	*next;

	if (!msh->cmd_list)
		return ;
	next = msh->cmd_list->next;
	if (!msh->cmd_list->mode || (!g_exit_status && msh->cmd_list->mode == '&')
		|| (g_exit_status && g_exit_status < 128 && msh->cmd_list->mode == '|'))
		exec_pipeline(msh);
	ft_free_cmd_list_block(&msh->cmd_list);
	msh->cmd_list = next;
	exec_cmd_list(msh);
}

static int	sline_cmp_len(t_msh *msh)
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

static void	parse_exec_prep(t_msh *msh)
{
	char	*line;
	char	*eline;

	msh->malloc_err_parse = 0;
	line = msh->sline;
	eline = line + ft_strlen(line);
	if (trim_whitespaces(&line, &eline))
		return ;
	if (!is_in_str(*msh->sline, STR_WHSPACE)
		&& ft_strncmp(msh->sline, msh->ex_sline, sline_cmp_len(msh)))
	{
		add_history(msh->sline);
		ft_free_str(&msh->ex_sline);
		msh->ex_sline = ft_strdup(msh->sline);
	}
	if (!syntax_check(line, eline))
	{
		msh->cmd_list = parse_list(line, eline, msh, 0);
		if (msh->cmd_list)
			exec_cmd_list(msh);
		else if (msh->malloc_err_parse)
			ft_putstr_fd("not enough heap memory to perform execution\n", 2);
	}
	else
		g_exit_status = 2;
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	(void)argc;
	(void)argv;
	if (msh_prep(&msh, envp))
		return (1);
	while (1)
	{
		signal_manager(MODE_INTR_CMD);
		msh.sline = NULL;
		msh.sline = readline("\033[1;36mminishell>> \033[0m");
		signal_manager(MODE_NITR);
		if (msh.sline)
		{
			if (ft_strlen(msh.sline) != 0)
				parse_exec_prep(&msh);
			ft_free_str(&msh.sline);
		}
		else
			return (ft_putstr_fd("exit\n", 1),
				ft_free_exit(&msh), g_exit_status);
	}
}
